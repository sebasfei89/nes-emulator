#include "./mos6502.h"

namespace nes {

void MOS6502::opADC(AddressingMode addrMode) {
    const uint8_t operand = readOperand(addrMode);
    const uint16_t tmp = mA + operand + testFlag(Flags::Carry);
    updateFlag(Flags::Carry, tmp > 0xFF);
    const bool overflow = !((mA ^ operand) & 0x80) && ((mA ^ tmp) & 0x80);
    updateFlag(Flags::Overflow, overflow);
    mA = (uint8_t)(tmp & 0xFF);
    updateNZStatusFlags(mA);
}

void MOS6502::opCMP(AddressingMode addrMode) {
    const uint8_t operand = readOperand(addrMode);
    updateFlag(Flags::Carry, operand <= mA);
    updateNZStatusFlags(mA - operand);
}

void MOS6502::opCPX(AddressingMode addrMode) {
    const uint8_t operand = readOperand(addrMode);
    updateFlag(Flags::Carry, operand <= mX);
    updateNZStatusFlags(mX - operand);
}

void MOS6502::opCPY(AddressingMode addrMode) {
    const uint8_t operand = readOperand(addrMode);
    updateFlag(Flags::Carry, operand <= mY);
    updateNZStatusFlags(mY - operand);
}

void MOS6502::opSBC(AddressingMode addrMode) {
    const uint8_t operand = ~readOperand(addrMode);
    const uint16_t tmp = mA + operand + testBit(mStatusFlags, Flags::Carry);
    updateFlag(Flags::Carry, tmp > 0xFF);
    const bool overflow = !((mA ^ operand) & 0x80) && ((mA ^ tmp) & 0x80);
    updateFlag(Flags::Overflow, overflow);
    mA = (uint8_t)(tmp & 0xFF);
    updateNZStatusFlags(mA);
}

}
