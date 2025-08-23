#ifndef _H_FRAMEBUFFER
#define _H_FRAMEBUFFER

#ifdef __cplusplus
extern "C" {
#endif

#include "std/types.h"

bool framebuffer_init();

uint64_t framebuffer_get_width();
uint64_t framebuffer_get_height();

uint32_t framebuffer_encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

void framebuffer_clear(uint32_t colour);

void framebuffer_set_pixel(uint64_t x, uint64_t y, uint32_t colour);

#ifdef __cplusplus
}
#endif

#endif