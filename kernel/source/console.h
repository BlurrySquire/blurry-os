#ifndef _H_CONSOLE
#define _H_CONSOLE

#include <stdint.h>

#include <limine.h>

#define RGB(r, g, b) (uint32_t)((((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 0))

#define CONSOLE_COLOUR_BLACK   RGB(0x10, 0x10, 0x10)
#define CONSOLE_COLOUR_RED     RGB(0xC0, 0x00, 0x00)
#define CONSOLE_COLOUR_GREEN   RGB(0x00, 0xAF, 0x00)
#define CONSOLE_COLOUR_YELLOW  RGB(0xE1, 0xA9, 0x00)
#define CONSOLE_COLOUR_BLUE    RGB(0x0F, 0x28, 0xFF)
#define CONSOLE_COLOUR_MAGENTA RGB(0xCC, 0x00, 0xCC)
#define CONSOLE_COLOUR_CYAN    RGB(0x00, 0xAF, 0xAF)
#define CONSOLE_COLOUR_WHITE   RGB(0xC3, 0xC3, 0xC3)

/* Change the limine framebuffer to use. */
void console_set_framebuffer(struct limine_framebuffer* framebuffer);

/* Set the foreground (text) and background colour to use. */
void console_set_colour(uint32_t foreground, uint32_t background);

/* Clear the console. */
void console_clear();

void console_print_char(const char character);
void console_print(const char* string);

#endif