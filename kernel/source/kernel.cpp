#include "std/int.h"
#include "std/def.h"
#include "std/string.h"

#include "limine.h"
#include "limine_requests.h"

#include "panic.hpp"

#include "framebuffer.h"
#include "console/console.h"
#include "serial.h"

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

        serial_printf("Hypervisor present: %s\n", vendor);
    }

    framebuffer_init();
    console_init();
    console_clear();

    console_printf("Hello, kernel!\n");
    serial_printf("Hello, serial!\n");

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

        serial_init();
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