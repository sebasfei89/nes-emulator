#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opDEC(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        updateNZStatusFlags(--operand);
        return operand;
    });
}

void MOS6502::opDEX(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    updateNZStatusFlags(--mX);
    ++mCyclesUsed;
}

void MOS6502::opDEY(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    updateNZStatusFlags(--mY);
    ++mCyclesUsed;
}

void MOS6502::opINC(AddressingMode addrMode) {
    readModifyWrite(addrMode, [this](uint8_t operand) {
        updateNZStatusFlags(++operand);
        return operand;
    });
}

void MOS6502::opINX(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    updateNZStatusFlags(++mX);
    ++mCyclesUsed;
}

void MOS6502::opINY(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    updateNZStatusFlags(++mY);
    ++mCyclesUsed;
}

}
