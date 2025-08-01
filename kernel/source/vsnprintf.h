#ifndef _H_VSNPRINTF
#define _H_VSNPRINTF

#include <stdarg.h>
#include <stddef.h>

void vsnprintf(char* out, size_t maxlen, const char* format, va_list args);

#endif