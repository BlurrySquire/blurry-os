#ifndef _H_SERIAL
#define _H_SERIAL

int serial_init();

void serial_send_char(const char character);
void serial_send_string(const char* string);

char serial_receive_char();

#endif