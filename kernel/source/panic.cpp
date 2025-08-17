#include "panic.hpp"

#include "std/string.h"

#include "serial.hpp"

void KernelPanic(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[512];
    string_vnprintf(buffer, sizeof(buffer), fmt, args);

    Serial::Print("PANIC: %s\n", buffer);
}

[[noreturn]] void KernelHang() {
    while (true) {
        asm volatile (
            "hlt"
        );
    }
}