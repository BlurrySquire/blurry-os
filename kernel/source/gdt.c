#include "gdt.h"

#include "console.h"
#include "memory.h"

struct gdt_entry_t {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
};

struct gdtr_t {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

/*
    I am pretty sure that you cannot have the
    GDT as a local variable, as it needs to
    stay in RAM. I think local variables get
    discarded as free memory after a function
    is finished. So therefore making the GDT
    invalid eventually.
*/

uint64_t gdt[5];

uint64_t gdt_encode_entry(struct gdt_entry_t entry) {
    if (entry.limit > 0xFFFFF) {
        console_set_colour(CONSOLE_COLOUR_WHITE, CONSOLE_COLOUR_RED);
        console_print("GDT: Cannot encode limits larger than 0xFFFFF.\n");
        return 0x00ULL;
    }

    uint8_t encoded[8];

    // Encode the limit
    encoded[0] = entry.limit & 0xFF;
    encoded[1] = (entry.limit >> 8) & 0xFF;
    encoded[6] = (entry.limit >> 16) & 0x0F;

    // Encoded the base
    encoded[2] = entry.base & 0xFF;
    encoded[3] = (entry.base >> 8) & 0xFF;
    encoded[4] = (entry.base >> 16) & 0xFF;
    encoded[7] = (entry.base >> 24) & 0xFF;
    
    // Encode access byte
    encoded[5] = entry.access_byte;

    // Encode the flags
    encoded[6] |= (entry.flags << 4);

    uint64_t result;
    memcpy(&result, encoded, sizeof(result));
    
    return result;
}

void gdt_set_gdtr(struct gdtr_t gdtr) {
    asm volatile (
        "lgdt %0\n"
        "pushq $0x08\n"
        "lea 1f(%%rip), %%rax\n"
        "pushq %%rax\n"
        "lretq\n"
        "1:\n"
        :
        : "m"(gdtr)
        : "memory", "rax"
    );
}

void gdt_setup() {
    // TODO: TASK STATE SEGMENT
    // DO THIS LATER, IT CAN WAIT

    struct gdt_entry_t null_descriptor = {
        0, 0, 0, 0
    };
    struct gdt_entry_t kernel_code_segment = {
        0, 0xFFFFF, 0x9A, 0xA
    };
    struct gdt_entry_t kernel_data_segment = {
        0, 0xFFFFF, 0x92, 0xC
    };
    struct gdt_entry_t user_code_segment = {
        0, 0xFFFFF, 0xFA, 0xA
    };
    struct gdt_entry_t user_data_segment = {
        0, 0xFFFFF, 0xF2, 0xC
    };

    gdt[0] = gdt_encode_entry(null_descriptor);
    gdt[1] = gdt_encode_entry(kernel_code_segment);
    gdt[2] = gdt_encode_entry(kernel_data_segment);
    gdt[3] = gdt_encode_entry(user_code_segment);
    gdt[4] = gdt_encode_entry(user_data_segment);

    struct gdtr_t gdtr = {
        sizeof(gdt) - 1,
        (uint64_t)gdt
    };

    gdt_set_gdtr(gdtr);

    asm volatile (
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :
        :
        : "ax"
    );
}