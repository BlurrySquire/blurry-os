#include "framebuffer.h"

#include "std/def.h"

#include "limine_requests.h"

bool _fb_init = false;
struct limine_framebuffer* _framebuffer = NULL;

bool framebuffer_init() {
    if (_fb_init) return false;

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        // Throw an error
        _fb_init = false;
        return _fb_init;
    }

    _framebuffer = framebuffer_request.response->framebuffers[0];

    _fb_init = true;
    return _fb_init;
}

uint64_t framebuffer_get_width() {
    if (_framebuffer == NULL) return 0;

    return _framebuffer->width;
}

uint64_t framebuffer_get_height() {
    if (_framebuffer == NULL) return 0;

    return _framebuffer->height;
}

uint32_t framebuffer_encode_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t colour = 0x00000000;

    colour |= (uint32_t)red << _framebuffer->red_mask_shift;
    colour |= (uint32_t)green << _framebuffer->green_mask_shift;
    colour |= (uint32_t)blue << _framebuffer->blue_mask_shift;

    return colour;
}

void framebuffer_clear(uint32_t colour) {
    for (size_t y = 0; y < _framebuffer->height; y++) {
        for (size_t x = 0; x < _framebuffer->width; x++) {
            framebuffer_set_pixel(x, y, colour);
        }
    }
}

void framebuffer_set_pixel(uint64_t x, uint64_t y, uint32_t colour) {
    if (x > _framebuffer->width) return;
    if (y > _framebuffer->height) return;

    volatile uint32_t* pixels = _framebuffer->address;
    pixels[y * (_framebuffer->pitch / 4) + x] = colour;
}