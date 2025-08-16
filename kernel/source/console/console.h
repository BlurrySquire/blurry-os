#ifndef _H_CONSOLE
#define _H_CONSOLE

#ifdef __cplusplus
extern "C" {
#endif

#include "types/int.h"

#include "limine.h"

#define CONSOLE_MAX_STRING_LEN 512

#define CONSOLE_COLOUR_RGB(r, g, b) (uint32_t)((((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 0))

#define CONSOLE_COLOUR_BLACK   CONSOLE_COLOUR_RGB(0x10, 0x10, 0x10)
#define CONSOLE_COLOUR_RED     CONSOLE_COLOUR_RGB(0xC0, 0x00, 0x00)
#define CONSOLE_COLOUR_GREEN   CONSOLE_COLOUR_RGB(0x00, 0xAF, 0x00)
#define CONSOLE_COLOUR_YELLOW  CONSOLE_COLOUR_RGB(0xE1, 0xA9, 0x00)
#define CONSOLE_COLOUR_BLUE    CONSOLE_COLOUR_RGB(0x0F, 0x28, 0xFF)
#define CONSOLE_COLOUR_MAGENTA CONSOLE_COLOUR_RGB(0xCC, 0x00, 0xCC)
#define CONSOLE_COLOUR_CYAN    CONSOLE_COLOUR_RGB(0x00, 0xAF, 0xAF)
#define CONSOLE_COLOUR_WHITE   CONSOLE_COLOUR_RGB(0xC3, 0xC3, 0xC3)

void console_set_framebuffer(struct limine_framebuffer* framebuffer);

void console_set_colour(uint32_t foreground, uint32_t background);

void console_clear();

void console_putchar(const char character);
void console_putstr(const char* string);

void console_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif