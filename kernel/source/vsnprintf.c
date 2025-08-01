#include "vsnprintf.h"

#include <stdint.h>
#include <stdbool.h>

void format_int(int64_t value, char* buffer);
void format_uint(uint64_t value, char* buffer);
void format_hex(uint64_t value, bool uppercase, char* buffer);

void vsnprintf(char *out, size_t maxlen, const char *format, va_list args) {
    char* p = (char*)format;
    size_t i = 0;

    while (*p != '\0' && i < (maxlen - 1)) {
        if (*p == '%' && *(p + 1)) {
            p++;
            switch (*p) {
                case '%': {
                    out[i++] = '%';

                    break;
                }

                case 'c': {
                    char c = (char)va_arg(args, int);
                    out[i++] = c;

                    break;
                }

                case 's': {
                    char* s = va_arg(args, char*);
                    while (*s != '\0') {
                        out[i++] = *s;
                        s++;
                    }

                    break;
                }

                case 'i':
                case 'd': {
                    int d = va_arg(args, int);
                    char buffer[22];
                    format_int(d, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        out[i++] = buffer[j++];
                    }

                    break;
                }

                case 'u': {
                    int u = va_arg(args, unsigned int);
                    char buffer[22];
                    format_uint(u, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        out[i++] = buffer[j++];
                    }

                    break;
                }

                case 'l': {
                    p++;
                    if (*p == 'd' || *p == 'i') {
                        int64_t ld = va_arg(args, long);
                        char buffer[22];
                        format_int(ld, buffer);
                        
                        int j = 0;
                        while (buffer[j]) {
                            out[i++] = buffer[j++];
                        }

                        break;
                    }
                    else if (*p == 'u') {
                        uint64_t ld = va_arg(args, unsigned long);
                        char buffer[22];
                        format_uint(ld, buffer);
                        
                        int j = 0;
                        while (buffer[j]) {
                            out[i++] = buffer[j++];
                        }

                        break;
                    }
                    else {
                        break;
                    }
                }

                case 'x': {
                    unsigned long lu = va_arg(args, unsigned long);
                    char buffer[17];
                    format_hex(lu, false, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        out[i++] = buffer[j++];
                    }

                    break;
                }

                case 'X': {
                    unsigned long lu = va_arg(args, unsigned long);
                    char buffer[17];
                    format_hex(lu, true, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        out[i++] = buffer[j++];
                    }

                    break;
                }

                default: {
                    break;
                }
            }
        }
        else {
            out[i++] = *p;
        }
        
        p++;
    }

    out[i] = '\0';
}

void format_int(int64_t value, char* buffer) {
    char temp[22];
    bool negative = false;
    int i = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0) {
        negative = true;
        value = -value;
    }

    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (negative) {
        temp[i++] = '-';
    }

    int j = 0;
    while (i--) {
        buffer[j++] = temp[i];
    }
    buffer[j] = '\0';
}

void format_uint(uint64_t value, char* buffer) {
    char temp[22];
    int i = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    int j = 0;
    while (i--) {
        buffer[j++] = temp[i];
    }
    buffer[j] = '\0';
}

void format_hex(uint64_t value, bool uppercase, char* buffer) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    const char* hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    char temp[17];
    int i = 0;

    while (value > 0) {
        temp[i++] = hex_digits[value & 0xF];
        value >>= 4;
    }

    int j = 0;
    while (i--) {
        buffer[j++] = temp[i];
    }
    buffer[j] = '\0';
}