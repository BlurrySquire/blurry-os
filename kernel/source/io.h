#ifndef _H_IO
#define _H_IO

#include <stdint.h>

/*
    io_writex:
        Traditional names are: outb, outw and outl.
        I have chosen to use a more explicit naming
        scheme.
    
    io_readx:
        Traditional names are: inb, inw and inl.
        I have chosen to use a more explicit naming
        scheme.
*/

void io_write8(uint16_t port, uint8_t value);
void io_write16(uint16_t port, uint16_t value);
void io_write32(uint16_t port, uint32_t value);

uint8_t io_read8(uint16_t port);
uint16_t io_read16(uint16_t port);
uint32_t io_read32(uint16_t port);

void io_wait();

#endif