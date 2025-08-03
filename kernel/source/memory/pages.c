#include "pages.h"

#include "types/int.h"

#include "serial.h"

#define PHYSICAL_MEM_START  0xFFFF800000000000UL

uint64_t total_pages = 0;
uint64_t bitmap_size = 0;
uintptr_t bitmap_phys_addr = 0;

uint8_t* bitmap = NULL;

enum page_state {
    PAGE_STATE_FREE = 0,
    PAGE_STATE_USED = 1,
    PAGE_STATE_RESERVED = 2
};

void page_init_bitmap(struct limine_memmap_response* memmap) {
    // We need to get the total number of pages
    for (size_t i = 0; i < memmap->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap->entries[i];
        total_pages += entry->length / PAGE_SIZE;
    }

    bitmap_size = (total_pages + 3) / 4;

    // Now we need a good area to put the bitmap in memory
    for (size_t i = 0; i < memmap->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap->entries[i];

        if (entry->type == LIMINE_MEMMAP_USABLE && entry->length >= bitmap_size) {
            bitmap_phys_addr = entry->base;
            break;
        }
    }

    bitmap = (uint8_t*)(bitmap_phys_addr + PHYSICAL_MEM_START);

    // Fill in the bitmap with pages
    for (size_t i = 0; i < memmap->entry_count; i++) {
        struct limine_memmap_entry* entry = memmap->entries[i];

        enum page_state state;
        switch (entry->type) {
            case LIMINE_MEMMAP_USABLE:
                state = PAGE_STATE_FREE;
                break;
            
            case LIMINE_MEMMAP_RESERVED:
                state = PAGE_STATE_RESERVED;
                break;
            
            default:
                state = PAGE_STATE_RESERVED;
                break;
        }

        for (size_t j = 0; j < entry->length; j += PAGE_SIZE) {
            size_t page_index = (entry->base + j) / PAGE_SIZE;
            size_t byte_index = page_index / 4;
            size_t bit_offset = (page_index % 4) * 2;

            bitmap[byte_index] &= ~(0x3 << bit_offset);
            bitmap[byte_index] |= (state << bit_offset);
        }
    }
}

void* palloc() {
    uint64_t next_free_page = 0;

    for (size_t i = 0; i < bitmap_size; i++) {
        uint8_t byte = bitmap[i];
        for (size_t j = 0; j < 4; j ++) {
            if (((byte >> (j * 2)) & 0x3) == PAGE_STATE_FREE) {
                size_t byte_index = i;
                size_t bit_offset = j * 2;

                bitmap[byte_index] &= ~(0x3 << bit_offset);
                bitmap[byte_index] |= (PAGE_STATE_USED << bit_offset);

                next_free_page = (i * 4 + j) * PAGE_SIZE;

                break;
            }
        }
    }

    return (void*)next_free_page;
}

void pfree(void* page) {
    uint64_t page_num = ((uintptr_t)page) / PAGE_SIZE;
    size_t byte_index = page_num / 4;
    size_t bit_offset = (page_num % 4) * 2;

    bitmap[byte_index] &= ~(0x3 << bit_offset);
    bitmap[byte_index] |= (PAGE_STATE_FREE << bit_offset);
}