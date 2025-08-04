#ifndef _H_MEMORY
#define _H_MEMORY

#ifdef __cplusplus
extern "C" {
#endif

#include "types/def.h"

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
void* memmove(void* dest, const void* src, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);

#ifdef __cplusplus
}
#endif

#endif