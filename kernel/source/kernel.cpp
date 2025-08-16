#include "types/int.h"
#include "types/def.h"
#include "types/string.h"

#include "limine.h"
#include "limine_requests.h"

#include "panic.hpp"
#include "serial.hpp"

#include "console/console.h"

#include "memory/page_allocator.hpp"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

#define PHYSICAL_MEM_START 0xFFFF800000000000UL

bool hypervisor_is_present() {
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

void kernel_main() {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        /*
            Bootloader doesn't support our requested
            revision. It is probably best to just hang
            or shutdown.
        */
        KernelPanic("Limine requested base revision unsuported.");
    }

    if (hypervisor_is_present()) {
        char vendor[13];
        hypervisor_get_vendor(vendor);

        Serial::Print("Hypervisor present: %s\n", vendor);
    }
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        /*
            Either a display isn't connected or the
            bootloader was unable to get a framebuffer
            from the GPU.
        */
        KernelPanic("Unable to get a framebuffer from Limine.");
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    console_set_framebuffer(framebuffer);
    console_clear();

    console_printf("Hello, kernel!\n");
    Serial::Print("Hello, serial!\n");

    // I had to google the rainbow to double check the colours
    uint32_t colours[7] = {
        CONSOLE_COLOUR_RGB(255, 0, 0),    // Red
        CONSOLE_COLOUR_RGB(255, 127, 0),  // Orange
        CONSOLE_COLOUR_RGB(255, 255, 0),  // Yellow
        CONSOLE_COLOUR_RGB(0, 255, 0),    // Green
        CONSOLE_COLOUR_RGB(0, 0, 255),    // Blue
        CONSOLE_COLOUR_RGB(75, 0, 130),   // Indigo
        CONSOLE_COLOUR_RGB(148, 0, 211),  // Violet
    };

    const char* message = "Wow oh wow! The colour changes! It is rainbow and stuff";
    for (size_t i = 0; message[i] != '\0'; i++) {
        console_set_colour(colours[i % 7], CONSOLE_COLOUR_BLACK);
        console_putchar(message[i]);
    }
    console_putstr("\n\n");
    console_set_colour(CONSOLE_COLOUR_WHITE, CONSOLE_COLOUR_BLACK);
    
    KernelHang();
    KernelPanic("Kernel reached end of 'kernel_main' function.");
}

extern "C" {
    typedef void (*constructor)();
    constructor _ctors_start[0];
    constructor _ctors_end[0];

    /* From source/gdt.S */
    extern void LoadGDT(void);

    __attribute__((noreturn))
    void kernel_start(void) {
        if (LIMINE_BASE_REVISION_SUPPORTED == false) {
            while (true) {
                asm volatile (
                    "hlt"
                );
            }
        }

        LoadGDT();

        Serial::Init();
        Memory::InitPageAllocator();

        // Should later on move before the Serial::Init();
        // We need 2 serial init functions, once for
        // normal output and then one for debugger output.
        struct limine_executable_cmdline_response* cmdline = cmdline_request.response;
        if (string_compare(cmdline->cmdline, "DEBUG_GDB") == 0) {
            Serial::Print("Boot with debugging enabled.\n");
        }

        /* Call all global constructors for C++ objects */
        uint64_t count = ((uint64_t)&_ctors_end - (uint64_t)&_ctors_end) / sizeof(void*);
        for (uint64_t i = 0; i < count; i++) {
            _ctors_start[i]();
        }

        kernel_main();

        while (true) {
            asm volatile (
                "hlt"
            );
        }
    }
}