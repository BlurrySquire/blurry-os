#ifndef _H_IO
#define _H_IO

#ifdef __cplusplus
extern "C" {
#endif

#include "std/types.h"

void io_write8(uint16_t port, uint8_t value);
void io_write16(uint16_t port, uint16_t value);
void io_write32(uint16_t port, uint32_t value);

uint8_t io_read8(uint16_t port);
uint16_t io_read16(uint16_t port);
uint32_t io_read32(uint16_t port);

#ifdef __cplusplus
}
#endif

#endif