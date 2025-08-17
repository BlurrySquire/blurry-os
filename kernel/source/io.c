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
    uint8_t value;

    asm volatile (
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
        : "memory"
    );

    return value;
}

uint16_t io_read16(uint16_t port) {
    uint16_t value;

    asm volatile (
        "inw %1, %0"
        : "=a"(value)
        : "Nd"(port)
        : "memory"
    );

    return value;
}

uint32_t io_read32(uint16_t port) {
    uint32_t value;

    asm volatile (
        "inl %1, %0"
        : "=a"(value)
        : "Nd"(port)
        : "memory"
    );

    return value;
}