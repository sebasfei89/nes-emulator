#pragma once

#include "./bus.h"

#include <span>

namespace nes {

template<size_t AMMOUNT>
class Ram : public IBusListener
{
public:
    void reset() { memset(&mData, 0x00, AMMOUNT); }

    void load(uint16_t startAddr, std::span<const uint8_t> bytes) {
        std::memcpy(&mData[startAddr], bytes.data(), bytes.size_bytes());
    }

    uint8_t operator[](uint16_t addr) const {
        return mData[addr];
    }

    uint8_t &operator[](uint16_t addr) {
        return mData[addr];
    }

    bool onHandleWrite(uint16_t addr, uint8_t value) override {
        if (addr < AMMOUNT) {
            mData[addr] = value;
            return true;
        }
        return false;
    }

    bool onHandleRead(uint16_t addr, uint8_t& value) override {
        if (addr < AMMOUNT) {
            value = mData[addr];
            return true;
        }
        return false;
    }

private:
    uint8_t mData[AMMOUNT];
};

}
