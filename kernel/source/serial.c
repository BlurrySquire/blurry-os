#include "serial.h"

#include "io.h"

#include "vsnprintf.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

/*
    https://osdev.wiki/wiki/Serial_Ports#Port_Addresses
    
    Only the first 2 COM ports are available. The OSDev
    Wiki says that the location of the other ports are
    less reliable.
*/

#define PORT_COM1 0x3F8
#define PORT_COM2 0x2F8

bool init = false;

int serial_init() {
    io_write8(PORT_COM1 + 1, 0x00);    // Disable all interrupts
    io_write8(PORT_COM1 + 3, 0x80);    // Enable DLAB (baud rate divisor)
    io_write8(PORT_COM1 + 0, 0x00);    // Set divisor to 3 (lo byte) 38400 baud
    io_write8(PORT_COM1 + 1, 0x00);    //                  (hi byte)
    io_write8(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    io_write8(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-bye threshold
    io_write8(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    io_write8(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
    io_write8(PORT_COM1 + 0, 0xAE);    // Test serial chip by sending byte 0xAE

    if (io_read8(PORT_COM1 + 0) != 0xAE) {
        // The port is faulty
        init = false;
        return 1;
    }

    /*
        The port is not faulty so we can set it to normal operation mode
        (not-loopback with IRQs enabled and OUT#1, OUT#2 bits enabled)
    */
    io_write8(PORT_COM1 + 4, 0x0F);

    init = true;
    return 0;
}

void serial_putchar(const char character) {
    if (!init) return;

    while ((io_read8(PORT_COM1 + 5) & 0x20) == 0);

    io_write8(PORT_COM1, (uint8_t)character);
}

void serial_putstr(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\n') {
            serial_putchar('\r');
            serial_putchar('\n');
        }
        else {
            serial_putchar(string[i]);
        }
    }
}

void serial_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
}