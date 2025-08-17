#include "serial.h"

#include "std/args.h"
#include "std/string.h"

#include "io.h"

#define PORT_COM1 0x3F8

bool _serial_init = false;

bool serial_init() {
    if (_serial_init == true) return false;

    io_write8(PORT_COM1 + 1, 0x00);    // Disable all interrupts
    io_write8(PORT_COM1 + 3, 0x80);    // Enable DLAB (baud rate divisor)
    io_write8(PORT_COM1 + 0, 0x00);    // Set divisor to 3 (lo byte) 38400 baud
    io_write8(PORT_COM1 + 1, 0x00);    //                  (hi byte)
    io_write8(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    io_write8(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-bye threshold
    io_write8(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    io_write8(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
    io_write8(PORT_COM1 + 0, 0xAE);    // Test serial chip by sending byte 0xAE

    // If we don't read back 0xAE then the port is faulty
    if (io_read8(PORT_COM1 + 0) != 0xAE) {
        _serial_init = false;
        return _serial_init;
    }

    // Port is not faulty so set it to normal operation mode
    io_write8(PORT_COM1 + 4, 0x0F);

    _serial_init = true;
    return _serial_init;
}

void serial_putchar(const char character) {
    if (_serial_init == false) return;

    while ((io_read8(PORT_COM1 + 5) & 0x20) == 0);

    io_write8(PORT_COM1, (uint8_t)character);
}

void serial_putstr(const char* string) {
    if (_serial_init == false) return;

    for (uint64_t i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\t') {
            for (uint64_t i = 0; i < 4; i++) {
                serial_putchar(' ');
            }
        }
        else {
            serial_putchar(string[i]);
        }
    }
}

void serial_printf(const char* fmt, ...) {
    if (_serial_init == false) return;

    va_list args;
    va_start(args, fmt);

    char buffer[STRING_DEFAULT_MAX_LEN];
    string_vnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    serial_putstr(buffer);
}