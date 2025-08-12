#include "string.h"

#include "types/bool.h"

size_t strlen(const char* s) {
    size_t i = 0;

    while (s[i] != '\0') {
        i++;
    }

    return i;
}

int strcmp(const char *s1, const char *s2) {
    size_t i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' || s2[i] == '\0') {
            return 0;
        }

        i++;
    }

    return s1[i] - s2[i];
}

void strcpy(char *restrict dest, const char *restrict src) {
    size_t i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void string_vnprintf(char* dest, size_t maxlen, const char* fmt, va_list args) {
    char* p = (char*)fmt;
    size_t i = 0;

    while (*p != '\0' && i < (maxlen - 1)) {
        if (*p == '%' && *(p + 1)) {
            p++;
            switch (*p) {
                case '%': {
                    dest[i++] = '%';

                    break;
                }

                case 'c': {
                    char c = (char)va_arg(args, int);
                    dest[i++] = c;

                    break;
                }

                case 's': {
                    char* s = va_arg(args, char*);
                    while (*s != '\0') {
                        dest[i++] = *s;
                        s++;
                    }

                    break;
                }

                case 'i':
                case 'd': {
                    int d = va_arg(args, int);
                    char buffer[21];
                    string_format_int(d, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        dest[i++] = buffer[j++];
                    }

                    break;
                }

                case 'u': {
                    int u = va_arg(args, unsigned int);
                    char buffer[21];
                    string_format_uint(u, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        dest[i++] = buffer[j++];
                    }

                    break;
                }

                case 'l': {
                    p++;

                    switch (*p) {
                        case 'd':
                        case 'i': {
                            int64_t ld = va_arg(args, long);
                            char buffer[21];
                            string_format_int(ld, buffer);
                            
                            int j = 0;
                            while (buffer[j]) {
                                dest[i++] = buffer[j++];
                            }

                            break;
                        }

                        case 'u': {
                            uint64_t ld = va_arg(args, unsigned long);
                            char buffer[21];
                            string_format_uint(ld, buffer);
                            
                            int j = 0;
                            while (buffer[j]) {
                                dest[i++] = buffer[j++];
                            }

                            break;
                        }

                        case 'x': {
                            unsigned long lu = va_arg(args, unsigned long);
                            char buffer[17];
                            string_format_hex(lu, false, buffer);

                            int j = 0;
                            while (buffer[j]) {
                                dest[i++] = buffer[j++];
                            }

                            break;
                        }

                        case 'X': {
                            unsigned long lu = va_arg(args, unsigned long);
                            char buffer[17];
                            string_format_hex(lu, true, buffer);

                            int j = 0;
                            while (buffer[j]) {
                                dest[i++] = buffer[j++];
                            }

                            break;
                        }

                        default: {
                            break;
                        }
                    }

                    break;
                }

                case 'x': {
                    unsigned long u = va_arg(args, unsigned int);
                    char buffer[17];
                    string_format_hex(u, false, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        dest[i++] = buffer[j++];
                    }

                    break;
                }

                case 'X': {
                    unsigned long u = va_arg(args, unsigned int);
                    char buffer[17];
                    string_format_hex(u, true, buffer);

                    int j = 0;
                    while (buffer[j]) {
                        dest[i++] = buffer[j++];
                    }

                    break;
                }

                default: {
                    break;
                }
            }
        }
        else {
            dest[i++] = *p;
        }
        
        p++;
    }

    dest[i] = '\0';
}

void string_format_int(int64_t value, char buffer[21]) {
    char temp[21];
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

void string_format_uint(uint64_t value, char buffer[21]) {
    char temp[21];
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

void string_format_hex(uint64_t value, bool uppercase, char buffer[17]) {
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