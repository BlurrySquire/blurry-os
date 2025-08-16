#ifndef _HPP_SERIAL
#define _HPP_SERIAL

#define SERIAL_MAX_STRING_LEN 512

namespace Serial {
    // Just return a bool because if serial isn't enabled then we won't report any errors
    bool Init();

    void PutChar(const char charater);
    void PutStr(const char* string);

    void Print(const char* fmt, ...);
}

#endif