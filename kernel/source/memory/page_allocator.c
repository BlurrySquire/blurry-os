#include "page_allocator.h"

#include "limine.h"
#include "limine_requests.h"

#include "serial.h"

#define PAGES_PER_BYTE 8

uint64_t _total_pages = 0;
uint64_t _bitmap_size = 0;
uintptr_t _bitmap_addr = 0;
uint8_t* _bitmap = NULL;
uint64_t _last_bitmap_index = 0;

enum page_state {
    PAGE_STATE_FREE = 0,
    PAGE_STATE_USED = 1
};

// TODO: Avoid as many for loops

// TODO: If coming back here, you may as well just rewrite everything.

void page_allocator_init() {
    struct limine_memmap_response* memmap = memmap_request.response;
    struct limine_hhdm_response* hhdm = hhdm_request.response;

    for (uint64_t i = 0; i < memmap->entry_count; i++) {
        _total_pages += memmap->entries[i]->length / PAGE_SIZE;
    }

    _bitmap_size = (_total_pages) / PAGES_PER_BYTE;

    for (uint64_t i = 0; i < memmap->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE && entry->length >= _bitmap_size) {
            // If we can be divided cleanly by
            // page size then we are aligned.
            if (entry->length % PAGE_SIZE == 0) {
                _bitmap_addr = entry->base;
                break;
            }
        }
    }

    // set the bitmap
    _bitmap = (uint8_t*)(_bitmap_addr + hhdm->offset);
    uint64_t bitmap_pages_start = _bitmap_addr / PAGE_SIZE;
    uint64_t bitmap_pages_count = _bitmap_size / PAGE_SIZE;
    if (_bitmap_size % PAGE_SIZE != 0) {
        bitmap_pages_count += 1;
    }

    for (uint64_t i = 0; i < memmap->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap->entries[i];

        enum page_state state;
        switch (entry->type) {
            case LIMINE_MEMMAP_USABLE:
                state = PAGE_STATE_FREE;
                break;
            
            default:
                state = PAGE_STATE_USED;
                break;
        }

        for (uint64_t j = 0; j < entry->length; j += PAGE_SIZE) {
            uint64_t page_index = (entry->base + j) / PAGE_SIZE;
            uint64_t byte_index = page_index / PAGES_PER_BYTE;
            uint8_t bit_offset = (page_index % PAGES_PER_BYTE);

            if (page_index >= bitmap_pages_start && page_index < bitmap_pages_start + bitmap_pages_count) {
                _bitmap[byte_index] |= (PAGE_STATE_USED << bit_offset);
            }
            else {
                _bitmap[byte_index] |= (state << bit_offset);
            }
        }
    }

    // Little hack, but ensure first page is reserved
    _bitmap[0] &= ~(1 << 0);
    _bitmap[0] |= (PAGE_STATE_USED << 0);
}

void* page_alloc(size_t count) {
    uint64_t first_page = 0;
    size_t pages_found = 0;

    // Just loop through until we find enough consecutive pages
    for (uint64_t i = 0; i < _bitmap_size; i++) {
        uint8_t byte = _bitmap[i];
        for (uint8_t j = 0; j < PAGES_PER_BYTE; j++) {
            if ((byte & (1 << j)) == (PAGE_STATE_FREE << j)) {
                if (pages_found == 0) {
                    serial_printf("page_alloc: found first free page.\n");
                    first_page = i * PAGES_PER_BYTE + j;
                }
                pages_found += 1;

                serial_printf("page_alloc: got %i free pages out of %i free pages needed.\n", pages_found, count);

                if (pages_found == count) {
                    break;
                }
            }
            else {
                pages_found = 0;
            }
        }

        if (pages_found == count) {
            break;
        }
    }

    if (pages_found < count) {
        return NULL;
    }

    // Now mark all those pages as used
    for (uint64_t i = first_page; i < first_page + count; i++) {
        uint64_t byte_index = i / PAGES_PER_BYTE;
        uint8_t bit_offset = i % PAGES_PER_BYTE;

        uint8_t before = (_bitmap[byte_index] << bit_offset) & (1 << bit_offset);

        _bitmap[byte_index] &= ~(1 << bit_offset);
        _bitmap[byte_index] |= (PAGE_STATE_USED << bit_offset);

        uint8_t after = (_bitmap[byte_index] << bit_offset) & (1 << bit_offset);

        serial_printf("page_alloc: page_number %li before %i, after %i\n", i, before ? 1 : 0, after ? 1 : 0);
    }

    return (void*)(uintptr_t)((first_page * PAGE_SIZE) + hhdm_request.response->offset);
}

// TODO: It is easy to free more pages than you allocated
// and then free unrelated pages, which may have important
// data in them.
void page_free(void* data, size_t count) {
    uint64_t first_page = ((uintptr_t)data - hhdm_request.response->offset) / PAGE_SIZE;

    if ((first_page / PAGES_PER_BYTE) > _bitmap_size) {
        serial_printf("page_free: trying to free pages outside of bitmap.\n");
        return;
    }

    for (size_t i = first_page; i < first_page + count; i++) {
        uint64_t byte_index = i / PAGES_PER_BYTE;
        uint8_t bit_offset = i % PAGES_PER_BYTE;

        uint8_t before = (_bitmap[byte_index] << bit_offset) & (1 << bit_offset);

        _bitmap[byte_index] &= ~(1 << bit_offset);
        _bitmap[byte_index] |= (PAGE_STATE_FREE << bit_offset);

        uint8_t after = (_bitmap[byte_index] << bit_offset) & (1 << bit_offset);

        serial_printf("page_free: page_number %li before %i, after %i\n", i, before ? 1 : 0, after ? 1 : 0);
    }
}