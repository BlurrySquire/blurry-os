#ifndef _HPP_IO
#define _HPP_IO

#include "std/int.h"

namespace IO {
    void Write8(uint16_t port, uint8_t value);
    void Write16(uint16_t port, uint16_t value);
    void Write32(uint16_t port, uint32_t value);

    uint8_t Read8(uint16_t port);
    uint16_t Read16(uint16_t port);
    uint32_t Read32(uint16_t port);
}

#endif