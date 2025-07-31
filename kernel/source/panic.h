#ifndef _H_KERNEL_PANIC
#define _H_KERNEL_PANIC

void kernel_panic(const char* message);

[[noreturn]] void kernel_hang();

#endif