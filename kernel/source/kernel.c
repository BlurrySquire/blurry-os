#include "std/types.h"
#include "std/string.h"

#include "limine.h"
#include "limine_requests.h"

#include "framebuffer.h"
#include "console/console.h"
#include "serial.h"
#include "panic.h"

#include "memory/page_allocator.h"

/* From kernel/source/gdt.S */
extern void gdt_load(void);

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

void kernel_main() {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        while (true) {
            asm volatile (
                "hlt"
            );
        }
    }

    gdt_load();

    struct limine_executable_cmdline_response* cmdline = cmdline_request.response;
    if (string_compare(cmdline->cmdline, "DEBUG_GDB") == 0) {
        // We should at some point initialise serial to handle GDB
        // For now we initialise it as normal.
        // serial_printf("Boot with debugging enabled.\n");
    }

    serial_init();
    serial_printf("Hello, serial!\n");

    page_allocator_init();

    framebuffer_init();

    console_init();
    console_clear();
    console_printf("Hello, kernel!\n");

    // I had to google the rainbow to double check the colours
    uint8_t colours[7][3] = {
        {255, 0, 0},    // Red
        {255, 127, 0},  // Orange
        {255, 255, 0},  // Yellow
        {0, 255, 0},    // Green
        {0, 0, 255},    // Blue
        {75, 0, 130},   // Indigo
        {148, 0, 211},  // Violet
    };

    const char* message = "Wow oh wow! The colour changes! It is rainbow and stuff";
    for (size_t i = 0; message[i] != '\0'; i++) {
        uint8_t* colour = colours[i % 7];
        console_set_foreground(colour[0], colour[1], colour[2]);
        console_putchar(message[i]);
    }
    console_putstr("\n\n");
    console_set_foreground(CONSOLE_COLOUR_WHITE);
    
    kernel_hang();
    kernel_panic("Kernel reached end of 'kernel_main' function.");
}