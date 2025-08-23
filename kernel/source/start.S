.section .bss
.align 16
stack_bottom:
    .skip 0x8000    /* 32KiB */
stack_top:

.section .text
.global _start

_start:
    leaq stack_top(%rip), %rsp
    call kernel_main
    jmp _loop

_loop:
    hlt
    jmp _loop