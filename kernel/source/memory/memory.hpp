#ifndef _HPP_MEMORY_MEMORY
#define _HPP_MEMORY_MEMORY

#include "std/int.h"

namespace Memory {
    void* memcpy(void* dest, const void* src, size_t n);
    void* memset(void* s, int c, size_t n);
    void* memmove(void* dest, const void* src, size_t n);
    int memcmp(const void* s1, const void* s2, size_t n);
}

#endif