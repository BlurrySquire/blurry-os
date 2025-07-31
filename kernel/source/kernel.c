#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <limine.h>

#include "limine_requests.h"
#include "console.h"
#include "serial.h"
#include "panic.h"

#include "gdt.h"

void kernel_main(void) {
    /*
        Serial is really useful for printing errors
        and useful info when nothing else on the
        device is setup, so we initialise it first.
    */
    serial_init();
    
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        /*
            Bootloader doesn't support our requested
            revision. It is probably best to just hang
            or shutdown.
        */
        kernel_panic("Limine requested base revision unsuported.");
    }

    gdt_setup();

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        /*
            Either a display isn't connected or the
            bootloader was unable to get a framebuffer
            from the GPU.
        */
        kernel_panic("Unable to get a framebuffer from Limine.");
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    console_set_framebuffer(framebuffer);
    console_clear();

    console_print("Hello, kernel!\n");
    console_print("Hello, kernel!\n");

    serial_send_string("Hello, serial!\n");
    
    kernel_panic("Kernel reached end of 'kernel_main' function.");
}