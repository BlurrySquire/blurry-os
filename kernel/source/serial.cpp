#include "serial.hpp"

#include "types/args.h"
#include "types/string.h"

#include "io.hpp"

#define PORT_COM1 0x3F8

bool _init = false;

namespace Serial {
    bool Init() {
        if (_init == true) {
            return false;
        }

        IO::Write8(PORT_COM1 + 1, 0x00);    // Disable all interrupts
        IO::Write8(PORT_COM1 + 3, 0x80);    // Enable DLAB (baud rate divisor)
        IO::Write8(PORT_COM1 + 0, 0x00);    // Set divisor to 3 (lo byte) 38400 baud
        IO::Write8(PORT_COM1 + 1, 0x00);    //                  (hi byte)
        IO::Write8(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
        IO::Write8(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-bye threshold
        IO::Write8(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
        IO::Write8(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
        IO::Write8(PORT_COM1 + 0, 0xAE);    // Test serial chip by sending byte 0xAE

        // If we don't read back 0xAE then the port is faulty
        if (IO::Read8(PORT_COM1 + 0) != 0xAE) {
            _init = false;
            return _init;
        }

        // Port is not faulty so set it to normal operation mode
        IO::Write8(PORT_COM1 + 4, 0x0F);

        _init = true;
        return _init;
    }

    void PutChar(const char character) {
        if (_init == false) {
            return;
        }

        while ((IO::Read8(PORT_COM1 + 5) & 0x20) == 0);

        IO::Write8(PORT_COM1, (uint8_t)character);
    }

    void PutStr(const char* string) {
        if (_init == false) {
            return;
        }

        for (uint64_t i = 0; string[i] != '\0'; i++) {
            if (string[i] == '\n') {
                PutChar('\r');
                PutChar('\n');
            }
            else if (string[i] == '\t') {
                for (uint64_t i = 0; i < 4; i++) {
                    PutChar(' ');
                }
            }
            else {
                PutChar(string[i]);
            }
        }
    }

    void Print(const char* fmt, ...) {
        if (_init == false) {
            return;
        }

        va_list args;
        va_start(args, fmt);

        char buffer[512];
        vsnprintf(buffer, sizeof(buffer), fmt, args);

        va_end(args);

        Serial::PutStr(buffer);
    }
}