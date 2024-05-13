#pragma once

#include <cstdint>
#include <cstring>

namespace nes {

template<size_t AMMOUNT>
struct Ram
{
    uint8_t mData[AMMOUNT];

    void reset() { memset(&mData, 0x00, AMMOUNT); }
};

}
