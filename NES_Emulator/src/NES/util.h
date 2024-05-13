#pragma once

#include <cstdint>

namespace nes {

constexpr uint8_t testBit(uint8_t value, uint8_t bit) { return (value >> bit) & 1; }
constexpr void setBit(uint8_t& value, uint8_t bit) { value = value | 1 << bit; }
constexpr void clearBit(uint8_t& value, uint8_t bit) { value = value & ~(1 << bit); }
constexpr void updateBit(uint8_t &value, uint8_t bit, bool set = true) { set ? setBit(value, bit) : clearBit(value, bit); }

constexpr uint8_t hiByte(uint16_t word) { return (uint8_t)(word >> 8); }
constexpr uint8_t loByte(uint16_t word) { return (uint8_t)(word & 0x00FF); }

constexpr size_t CARTRIDGE_RAM_AMMOUT = 40 * 1024 + 6;

constexpr uint16_t STACK_ADDRESS = 0x01FF;
constexpr uint16_t PPU_REGISTERS_ADDRESS = 0x2000;
constexpr uint16_t CARTRIDGE_INIT_ADDRESS = 0x4020;
constexpr uint16_t RESET_ADDRESS = 0xFFFC;
constexpr uint16_t IRQ_VECTOR_ADDRESS = 0xFFFE;

}
