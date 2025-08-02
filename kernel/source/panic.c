#include "panic.h"

#include "serial.h"

#include "console/console.h"

#include <stdint.h>
#include <stdbool.h>

/*
    It is really rare for serial to
    cause a kernel panic, so we can
    output to serial for every panic.

    However, the console is more likely
    to cause a kernel panic, so we
    will only output to it for the first
    panic recieved.

    This avoids an infinite loop of panics.
*/

uint8_t counter = 0;

void kernel_panic(const char* message) {
    if (counter < 1) {
        counter++;    
    
        console_set_colour(CONSOLE_COLOUR_WHITE, CONSOLE_COLOUR_RED);
        console_printf("PANIC: %s\n", message);
    }
    serial_printf("PANIC: %s\n", message);

    kernel_hang();
}

[[noreturn]] void kernel_hang() {
    while (true) {
        asm volatile(
            "hlt"
        );
    }
}