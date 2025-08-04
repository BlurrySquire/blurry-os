#ifndef _H_KERNEL_PANIC
#define _H_KERNEL_PANIC

#ifdef __cplusplus
extern "C" {
#endif

void kernel_panic(const char* message);

[[noreturn]] void kernel_hang();

#ifdef __cplusplus
}
#endif

#endif