#ifndef _H_STRING
#define _H_STRING

#ifdef __cplusplus
extern "C" {
#endif

#include "std/types.h"
#include "std/va_args.h"

#define STRING_DEFAULT_MAX_LEN 512

size_t string_length(const char* str);
int string_compare(const char* str1, const char* str2);
void string_copy(char* dest, const char* src);

void string_format_int(int64_t value, char buffer[21]);
void string_format_uint(uint64_t value, char buffer[21]);
void string_format_hex(uint64_t value, bool uppercase, char buffer[17]);

void string_vnprintf(char* dest, size_t maxlen, const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif