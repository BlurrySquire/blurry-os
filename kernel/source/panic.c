#include "panic.h"

#include "serial.h"
#include "console.h"

#include <stdbool.h>

void kernel_panic(const char* message) {
    serial_send_string("PANIC: ");
    serial_send_string(message); 
    serial_send_string("\n");

    kernel_hang();
}

[[noreturn]] void kernel_hang() {
    while (true) {
        asm volatile(
            "hlt"
        );
    }
}