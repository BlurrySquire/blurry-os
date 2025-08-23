.section .data
gdt:
    .quad 0x0000000000000000 // null
    .quad 0x00AF9A000000FFFF // kernel code
    .quad 0x00CF92000000FFFF // kernel data
    .quad 0x00AFFA000000FFFF // user code
    .quad 0x00CFF2000000FFFF // user data
    // TODO: task state segment
gdt_end:
gdtr:
    .word gdt_end - gdt - 1
    .quad gdt

.section .text
.global gdt_load
.type gdt_load, @function

gdt_load:
    lgdt gdtr

    mov $0x10, %rax
    mov %rax, %ds
    mov %rax, %es
    mov %rax, %ss
    mov %rax, %fs
    mov %rax, %gs

    lea .flush, %rax
    ret

    push %rax
    retf

.flush:
    ret