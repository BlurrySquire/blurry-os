#ifndef _H_PANIC
#define _H_PANIC

#ifdef __cplusplus
extern "C" {
#endif

void kernel_panic(const char* fmt, ...);

__attribute__((noreturn)) void kernel_hang();

#ifdef __cplusplus
}
#endif

#endif