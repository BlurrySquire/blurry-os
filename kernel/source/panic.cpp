#include "panic.hpp"

#include "types/string.h"

#include "serial.hpp"

void KernelPanic(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    Serial::Print("PANIC: %s\n", buffer);
}

[[noreturn]] void KernelHang() {
    while (true) {
        asm volatile (
            "hlt"
        );
    }
}