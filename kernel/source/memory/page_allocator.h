#ifndef _H_MEMORY_PAGE_ALLOCATOR
#define _H_MEMORY_PAGE_ALLOCATOR

#ifdef __cplusplus
extern "C" {
#endif

#include "std/types.h"

#define PAGE_SIZE 4096

void page_allocator_init();

void* page_alloc(size_t count);
void page_free(void* data, size_t count);

#ifdef __cplusplus
}
#endif

#endif