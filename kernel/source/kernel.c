#include "types/int.h"
#include "types/bool.h"
#include "types/def.h"

#include <limine.h>

#include "limine_requests.h"
#include "serial.h"
#include "panic.h"

#include "console/console.h"

#include "gdt.h"

bool hypervisor_is_present(void) {
    uint32_t eax = 1, ebx, ecx, edx;
    asm volatile (
        "cpuid"
        : "+a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    );
    return ((ecx >> 31) & 1);
}

void hypervisor_get_vendor(char vendor[13]) {
    uint32_t eax = 0x40000000, ebx, ecx, edx;

    asm volatile (
        "cpuid"
        : "+a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    );

    *(uint32_t*)(vendor + 0) = ebx;
    *(uint32_t*)(vendor + 4) = ecx;
    *(uint32_t*)(vendor + 8) = edx;

    vendor[12] = '\0';
}

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

    if (hypervisor_is_present()) {
        char vendor[13];
        hypervisor_get_vendor(vendor);

        serial_printf("Hypervisor present: %s\n", vendor);
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

    console_printf("Hello, kernel!\n");
    serial_printf("Hello, serial!\n");
    
    kernel_panic("Kernel reached end of 'kernel_main' function.");
}