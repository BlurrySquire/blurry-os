#include "io.hpp"

namespace IO {
    void Write8(uint16_t port, uint8_t value) {
        asm volatile (
            "outb %%al, %w1"
            :
            : "a"(value), "Nd"(port)
        );
    }

    void Write16(uint16_t port, uint16_t value) {
        asm volatile (
            "outw %%ax, %w1"
            :
            : "ax"(value), "Nd"(port)
        );
    }

    void Write32(uint16_t port, uint32_t value) {
        asm volatile (
            "outl %%eax, %w1"
            :
            : "eax"(value), "Nd"(port)
        );
    }

    uint8_t Read8(uint16_t port) {
        uint8_t return_value;

        asm volatile (
            "inb %w1, %b0"
            : "=a"(return_value)
            : "Nd"(port)
            : "memory"
        );

        return return_value;
    }

    uint16_t Read16(uint16_t port) {
        uint16_t return_value;

        asm volatile (
            "inw %1, %0"
            : "=a"(return_value)
            : "Nd"(port)
            : "memory"
        );

        return return_value;
    }

    uint32_t Read32(uint16_t port) {
        uint32_t return_value;

        asm volatile (
            "inl %1, %0"
            : "=a"(return_value)
            : "Nd"(port)
            : "memory"
        );

        return return_value;
    }
}