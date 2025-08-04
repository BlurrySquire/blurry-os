#ifndef _H_SERIAL
#define _H_SERIAL

#ifdef __cplusplus
extern "C" {
#endif

int serial_init();

void serial_putchar(const char character);
void serial_putstr(const char* string);

void serial_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif