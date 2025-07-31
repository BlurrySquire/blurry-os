#include "panic.h"

#include "serial.h"
#include "console.h"

#include <stdbool.h>

void kernel_panic(const char* message) {
    console_set_colour(CONSOLE_COLOUR_WHITE, CONSOLE_COLOUR_RED);

    console_print("PANIC: ");
    console_print(message);
    console_print("\n");

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