#ifndef _H_STRING
#define _H_STRING

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#include "types/bool.h"
#endif

#include "types/int.h"
#include "types/args.h"

size_t strlen(const char* s);
int strcmp(const char* s1, const char* s2);
void strcpy(char* dest, const char* src);

void strfmt_int(int64_t value, char buffer[21]);
void strfmt_uint(uint64_t value, char buffer[21]);
void strfmt_hex(uint64_t value, bool uppercase, char buffer[17]);

void snprintf(char* dest, size_t maxlen, const char* fmt, ...);
void vsnprintf(char* dest, size_t maxlen, const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif