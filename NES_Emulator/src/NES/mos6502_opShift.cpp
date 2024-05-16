#include "./mos6502.h"

namespace nes {

void MOS6502::opASL(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        updateFlag(Flags::Carry, operand & 0x80);
        operand <<= 1;
        updateNZStatusFlags(operand);
        return operand;
    });
}

void MOS6502::opLSR(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        updateFlag(Flags::Carry, operand & 0x01);
        operand >>= 1;
        updateNZStatusFlags(operand);
        return operand;
    });
}

void MOS6502::opROL(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        uint8_t tmp = (operand << 1) | testFlag(Flags::Carry);
        updateFlag(Flags::Carry, operand & 0x80);
        operand = tmp;
        updateNZStatusFlags(operand);
        return operand;
    });
}

void MOS6502::opROR(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        uint8_t tmp = (operand >> 1) | testFlag(Flags::Carry) << 7;
        updateFlag(Flags::Carry, operand & 0x01);
        operand = tmp;
        updateNZStatusFlags(operand);
        return operand;
    });
}

}
