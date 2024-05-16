#include "./mos6502.h"

namespace nes {

void MOS6502::opAND(AddressingMode addrMode) {
    mA &= readOperand(addrMode);
    updateNZStatusFlags(mA);
}

void MOS6502::opBIT(AddressingMode addrMode) {
    const uint8_t operand = readOperand(addrMode);
    updateFlag(Flags::Negative, operand & 0x80);
    updateFlag(Flags::Overflow, operand & 0x40);
    updateFlag(Flags::Zero, !(operand & mA));
}

void MOS6502::opEOR(AddressingMode addrMode) {
    mA ^= readOperand(addrMode);
    updateNZStatusFlags(mA);
}

void MOS6502::opORA(AddressingMode addrMode) {
    mA |= readOperand(addrMode);
    updateNZStatusFlags(mA);
}

}
