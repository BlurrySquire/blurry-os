#include "types/int.h"
#include "types/def.h"

#include "limine.h"

#include "limine_requests.h"

#include "panic.hpp"
#include "serial.hpp"

#include "console/console.h"

#include "memory/pages.h"

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
    /*
        Serial is really useful for printing errors
        and useful info when nothing else on the
        device is setup, so we initialise it first.
    */
    Serial::Init();
    
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

    if (memmap_request.response == NULL) {
        KernelPanic("Unable to get memamp from Limine.\n");
    }

    struct limine_memmap_response* memmap_response = memmap_request.response;
    page_init_bitmap(memmap_response);

    void* address1 = palloc();
    Serial::Print("Allocated a page at address 0x%x\n", (uint64_t)address1);
    
    void* address2 = palloc();
    Serial::Print("Allocated a page at address 0x%x\n", (uint64_t)address2);
    
    pfree(address1);

    void* address3 = palloc();
    Serial::Print("Allocated a page at address 0x%x\n", (uint64_t)address3);

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

    console_printf("Hello, kernel!\n\n");
    Serial::Print("Hello, serial!\n");
    
    KernelHang();
    KernelPanic("Kernel reached end of 'kernel_main' function.");
}

extern "C" {
    typedef void (*constructor)();
    constructor _ctors_start[0];
    constructor _ctors_end[0];

    extern void LoadGDT(void);

    __attribute__((noreturn))
    void kernel_start(void) {
        LoadGDT();

        // Call all global constructors
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