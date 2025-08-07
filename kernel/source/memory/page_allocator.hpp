#ifndef _HPP_MEMORY_PAGE_ALLOCATOR
#define _HPP_MEMORY_PAGE_ALLOCATOR

#define PAGE_SIZE 4096

namespace Memory {
    void InitPageAllocator();

    void* PageAlloc();
    void PageFree(void* page);
}

#endif