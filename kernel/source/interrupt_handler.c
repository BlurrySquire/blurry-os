#include "std/types.h"

#include "serial.h"

struct cpu_status {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    uint64_t vector_number;
    uint64_t error_code;

    uint64_t rip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
};

void interrupt_handler(struct cpu_status context) {
    serial_printf("interrupt_handler: int %i, error %i\n", context.vector_number, context.error_code);
}