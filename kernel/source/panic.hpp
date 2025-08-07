#ifndef _HPP_KERNEL_PANIC
#define _HPP_KERNEL_PANIC

void KernelPanic(const char* fmt, ...);
[[noreturn]] void KernelHang();

#endif