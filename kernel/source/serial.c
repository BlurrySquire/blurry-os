#include "serial.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*
    https://osdev.wiki/wiki/Serial_Ports#Port_Addresses
    
    Only the first 2 COM ports are available. The OSDev
    Wiki says that the location of the other ports are
    less reliable.
*/

#define PORT_COM1 0x3F8
#define PORT_COM2 0x2F8

bool init = false;

void port_write(uint16_t port, uint8_t byte) {
    asm volatile (
        "out %0, %1"
        :
        : "a"(byte), "Nd"(port)
    );
}

uint8_t port_read(uint16_t port) {
    uint8_t byte;

    asm volatile (
        "in %1, %0"
        : "=a"(byte)
        : "Nd"(port)
    );

    return byte;
}

int serial_init() {
    port_write(PORT_COM1 + 1, 0x00);    // Disable all interrupts
    port_write(PORT_COM1 + 3, 0x80);    // Enable DLAB (baud rate divisor)
    port_write(PORT_COM1 + 0, 0x00);    // Set divisor to 3 (lo byte) 38400 baud
    port_write(PORT_COM1 + 1, 0x00);    //                  (hi byte)
    port_write(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    port_write(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-bye threshold
    port_write(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    port_write(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
    port_write(PORT_COM1 + 0, 0xAE);    // Test serial chip by sending byte 0xAE

    if (port_read(PORT_COM1 + 0) != 0xAE) {
        // The port is faulty
        init = false;
        return 1;
    }

    /*
        The port is not faulty so we can set it to normal operation mode
        (not-loopback with IRQs enabled and OUT#1, OUT#2 bits enabled)
    */
    port_write(PORT_COM1 + 4, 0x0F);

    init = true;
    return 0;
}

void serial_send_char(const char character) {
    if (!init) return;

    while ((port_read(PORT_COM1 + 5) & 0x20) == 0);

    port_write(PORT_COM1, (uint8_t)character);
}

void serial_send_string(const char* string) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\n') {
            serial_send_char('\r');
            serial_send_char('\n');
        }
        else {
            serial_send_char(string[i]);
        }
    }
}

char serial_receive_char() {
    if (!init) return 0;

    while ((port_read(PORT_COM1 + 5) & 1) == 0);

    return port_read(PORT_COM1);
}