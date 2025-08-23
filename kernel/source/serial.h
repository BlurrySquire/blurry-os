#ifndef _H_CONSOLE_SERIAL
#define _H_CONSOLE_SERIAL

#ifdef __cplusplus
extern "C" {
#endif

#include "std/types.h"

bool serial_init();

void serial_putchar(char character);
void serial_putstr(const char* string);

void serial_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif