#ifndef _H_MEMORY_PAGES
#define _H_MEMORY_PAGES

#include "types/def.h"

#include "limine.h"

#define PAGE_SIZE 4096

void page_init_bitmap(struct limine_memmap_response* memmap);

void* palloc();
void pfree(void* page);

#endif