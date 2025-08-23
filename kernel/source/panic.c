#include "panic.h"

#include "std/string.h"

#include "serial.h"

void kernel_panic(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[STRING_DEFAULT_MAX_LEN];
    string_vnprintf(buffer, sizeof(buffer), fmt, args);

    serial_printf("PANIC: %s\r\n", buffer);
}

void kernel_hang() {
    while (true) {
        asm volatile (
            "hlt"
        );
    }
}