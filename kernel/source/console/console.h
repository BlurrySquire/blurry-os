#ifndef _H_CONSOLE
#define _H_CONSOLE

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#include "std/bool.h"
#endif

#include "std/int.h"

#define CONSOLE_MAX_STRING_LEN 512

#define CONSOLE_COLOUR_BLACK   0x10, 0x10, 0x10
#define CONSOLE_COLOUR_RED     0xC0, 0x00, 0x00
#define CONSOLE_COLOUR_GREEN   0x00, 0xAF, 0x00
#define CONSOLE_COLOUR_YELLOW  0xE1, 0xA9, 0x00
#define CONSOLE_COLOUR_BLUE    0x0F, 0x28, 0xFF
#define CONSOLE_COLOUR_MAGENTA 0xCC, 0x00, 0xCC
#define CONSOLE_COLOUR_CYAN    0x00, 0xAF, 0xAF
#define CONSOLE_COLOUR_WHITE   0xC3, 0xC3, 0xC3

bool console_init();

void console_clear();

void console_set_foreground(uint8_t r, uint8_t g, uint8_t b);
void console_set_background(uint8_t r, uint8_t g, uint8_t b);

void console_putchar(const char character);
void console_putstr(const char* string);

void console_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif