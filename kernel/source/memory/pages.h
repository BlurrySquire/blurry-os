#ifndef _H_MEMORY_PAGES
#define _H_MEMORY_PAGES

#ifdef __cplusplus
extern "C" {
#endif

#include "types/def.h"

#include "limine.h"

#define PAGE_SIZE 4096

void page_init_bitmap(struct limine_memmap_response* memmap);

void* palloc();
void pfree(void* page);

#ifdef __cplusplus
}
#endif

#endif