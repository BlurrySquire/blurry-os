#include "console.h"

#include "std/string.h"
#include "std/args.h"
#include "std/def.h"

#include "font8x8_basic.h"
#include "framebuffer.h"

bool _console_init = false;
uint32_t _num_rows = 0;
uint32_t _num_cols = 0;
uint32_t _cursor_x = 0;
uint32_t _cursor_y = 0;
uint32_t _foreground = 0;
uint32_t _background = 0;
uint8_t _font_scale = 2;

bool console_init() {
    if (_console_init == true) return false;

    _num_rows = framebuffer_get_height() / FONT8X8_CHAR_SIZE / _font_scale;
    _num_cols = framebuffer_get_width() / FONT8X8_CHAR_SIZE / _font_scale;

    _foreground = framebuffer_encode_rgb(CONSOLE_COLOUR_WHITE);
    _background = framebuffer_encode_rgb(CONSOLE_COLOUR_BLACK);

    _console_init = true;
    return _console_init;
}

void console_set_foreground(uint8_t r, uint8_t g, uint8_t b) {
    _foreground = framebuffer_encode_rgb(r, g, b);
}

void console_set_background(uint8_t r, uint8_t g, uint8_t b) {
    _background = framebuffer_encode_rgb(r, g, b);
}

void console_clear() {
    if (_console_init == false) return;

    framebuffer_clear(_background);
}

void console_putchar(const char character) {
    if (_console_init == false) return;

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

    uint32_t x_offset = _cursor_x * 8 * _font_scale;
    uint32_t y_offset = _cursor_y * 8 * _font_scale;
    const char* glyph = font8x8_basic[(uint8_t)character];

    for (size_t y = 0; y < (8 * _font_scale); y++) {
        uint8_t row = glyph[y / _font_scale];
        for (size_t x = 0; x < (8 * _font_scale); x++) {
            uint32_t colour = (row & (1 << (x / _font_scale))) == (1 << (x / _font_scale)) ? _foreground : _background;
            framebuffer_set_pixel(x + x_offset, y + y_offset, colour);
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

    char buffer[CONSOLE_MAX_STRING_LEN];
    string_vnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    console_putstr(buffer);
}