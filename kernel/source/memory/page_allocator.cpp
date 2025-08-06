#include "page_allocator.hpp"

#include "limine.h"
#include "limine_requests.h"

#include "types/int.h"

#include "serial.hpp"

uint64_t _total_pages = 0;
uint64_t _bitmap_size = 0;
uintptr_t _bitmap_addr = 0;
uint8_t* _bitmap = nullptr;
uint64_t _last_bitmap_index = 0;

enum PageState {
    PAGE_STATE_FREE = 0,
    PAGE_STATE_USED = 1
};

namespace Memory {
    void InitPageAllocator() {
        struct limine_memmap_response* memmap = memmap_request.response;
        struct limine_hhdm_response* hhdm = hhdm_request.response;

        for (uint64_t i = 0; i < memmap->entry_count; i++) {
            _total_pages += memmap->entries[i]->length / PAGE_SIZE;
        }

        // 8 pages in a byte
        _bitmap_size = (_total_pages) / 8;

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

            PageState state;
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
                uint64_t byte_index = page_index / 8;
                uint8_t bit_offset = (page_index % 8);

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

    void* PageAlloc() {
        uintptr_t address = 0;

        for (uint64_t i = 0; i < _bitmap_size; i++) {
            uint8_t byte = _bitmap[i];
            for (uint8_t j = 0; j < 8; j++) {
                if (((byte >> j) & 1) == PAGE_STATE_FREE) {
                    _last_bitmap_index = i;

                    _bitmap[_last_bitmap_index] &= ~(1 << j);
                    _bitmap[_last_bitmap_index] |= (PAGE_STATE_USED << j);

                    address = (i * 8 + j) * PAGE_SIZE;
                    address += hhdm_request.response->offset;
                    return (void*)address;
                }
            }
        }

        return nullptr;
    }
    
    void PageFree(void* page) {
        uint64_t page_index = ((uintptr_t)page - hhdm_request.response->offset) / PAGE_SIZE;
        uint64_t byte_index = page_index / 8;
        uint8_t bit_offset = (page_index % 8);

        _bitmap[byte_index] &= ~(1 << bit_offset);
        _bitmap[byte_index] |= (PAGE_STATE_FREE << bit_offset);
    }
}