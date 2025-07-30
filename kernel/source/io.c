#include "io.h"

void io_write8(uint16_t port, uint8_t value) {
    asm volatile (
        "outb %%al, %w1"
        :
        : "a"(value), "Nd"(port)
    );
}

void io_write16(uint16_t port, uint16_t value) {
    asm volatile (
        "outw %%ax, %w1"
        :
        : "ax"(value), "Nd"(port)
    );
}

void io_write32(uint16_t port, uint32_t value) {
    asm volatile (
        "outl %%eax, %w1"
        :
        : "eax"(value), "Nd"(port)
    );
}

uint8_t io_read8(uint16_t port) {
    uint8_t return_value;

    asm volatile (
        "inb %w1, %b0"
        : "=a"(return_value)
        : "Nd"(port)
        : "memory"
    );

    return return_value;
}

uint16_t io_read16(uint16_t port) {
    uint16_t return_value;

    asm volatile (
        "inb %w1, %b0"
        : "=ax"(return_value)
        : "Nd"(port)
        : "memory"
    );

    return return_value;
}

uint32_t io_read32(uint16_t port) {
    uint32_t return_value;

    asm volatile (
        "inb %w1, %b0"
        : "=eax"(return_value)
        : "Nd"(port)
        : "memory"
    );

    return return_value;
}

void io_wait() {
    /*
        Write to port 0x80, as it is generally
        unused. This waits between 1 and 4
        microseconds.
    */

    io_write8(0x80, 0);
}