#include "console.h"

#include "font8x8_basic.h"

#include "types/string.h"
#include "types/args.h"
#include "types/def.h"

/* Internal variables use a '_' prefix. */
struct limine_framebuffer* _framebuffer = NULL;
uint16_t _num_rows = 0;
uint16_t _num_cols = 0;
uint16_t _cursor_x = 0;
uint16_t _cursor_y = 0;
uint32_t _foreground = CONSOLE_COLOUR_WHITE;
uint32_t _background = CONSOLE_COLOUR_BLACK;
uint8_t _scale = 2;

/* Internal functions use the same '_' prefix. */
void _framebuffer_set_pixel(uint32_t x, uint32_t y, uint32_t colour) {
    volatile uint32_t* pixels = _framebuffer->address;
    pixels[y * (_framebuffer->pitch / 4) + x] = colour;
}

void console_set_framebuffer(struct limine_framebuffer *framebuffer) {
    if (framebuffer == NULL) {
        return;
    }

    _framebuffer = framebuffer;
    _num_rows = framebuffer->height / 8 / _scale;
    _num_cols = framebuffer->width / 8 / _scale;
}

void console_set_colour(uint32_t foreground, uint32_t background) {
    _foreground = foreground;
    _background = background;
}

void console_clear() {
    if (_framebuffer == NULL) {
        return;
    }

    for (size_t y = 0; y < _framebuffer->height; y++) {
        for (size_t x = 0; x < _framebuffer->width; x++) {
            _framebuffer_set_pixel(x, y, _background);
        }
    }
}

void console_putchar(const char character) {
    if (_framebuffer == NULL) {
        return;
    }

    if (character < 0) {
        return;
    }
    else if (character == '\n') {
        _cursor_y += 1;
        _cursor_x = 0;
        return;
    }
    else if (character == '\t') {
        for (size_t i = 0; i < 4; i++) {
            console_putchar(' ');
        }
        return;
    }

    uint32_t x_offset = _cursor_x * 8 * _scale;
    uint32_t y_offset = _cursor_y * 8 * _scale;
    const char* glyph = font8x8_basic[(uint8_t)character];

    for (size_t y = 0; y < (8 * _scale); y++) {
        uint8_t row = glyph[y / _scale];
        for (size_t x = 0; x < (8 * _scale); x++) {
            uint32_t colour = (row & (1 << (x / _scale))) == (1 << (x / _scale)) ? _foreground : _background;
            _framebuffer_set_pixel(x + x_offset, y + y_offset, colour);
        }
    }

    _cursor_x += 1;
    if (_cursor_x > _num_cols) {
        _cursor_y += 1;
        _cursor_x = 0;
    }
}

void console_putstr(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        console_putchar(string[i]);
    }
}

void console_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    console_putstr(buffer);
}