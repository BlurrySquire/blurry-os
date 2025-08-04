#ifndef _H_STRING
#define _H_STRING

#ifdef __cplusplus
extern "C" {
#endif

#include "types/def.h"
#include "types/args.h"

size_t strlen(const char* s);
int strcmp(const char *s1, const char *s2);
void strcpy(char *restrict dest, const char *restrict src);

void snprintf(char* dest, size_t maxlen, const char* fmt, ...);
void vsnprintf(char* dest, size_t maxlen, const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif