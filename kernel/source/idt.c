#include "idt.h"

#include "std/types.h"

#include "serial.h"

struct idtr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct interrupt_descriptor {
    uint16_t address_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t address_med;
    uint32_t address_high;
    uint32_t reserved;
} __attribute__((packed));

struct interrupt_descriptor idt[256];

void idt_set_entry(uint8_t vector, void* handler, uint8_t dpl) {
    uint64_t handler_addr = (uintptr_t)handler;

    struct interrupt_descriptor* entry = &idt[vector];
    
    entry->address_low = handler_addr & 0xFFFF;
    entry->address_med = (handler_addr >> 16) & 0xFFFF;
    entry->address_high = handler_addr >> 32;
    entry->selector = 0x08;
    entry->flags = 0b1110 | ((dpl & 0xb11) << 5) | (1 << 7); // trap gate + present bit + DPL
    entry->ist = 0;
    entry->reserved = 0;
}

extern char vector_0_handler[];

void idt_load() {
    for (size_t i = 0; i < 256; i++) {
        idt_set_entry(i, (void*)(uint64_t)vector_0_handler + (i * 16), 0);
    }

    struct idtr idt_reg;
    idt_reg.limit = sizeof(idt) - 1;
    idt_reg.base = (uintptr_t)idt;

    asm volatile (
        "lidt %0"
        :
        : "m"(idt_reg)
    );
}