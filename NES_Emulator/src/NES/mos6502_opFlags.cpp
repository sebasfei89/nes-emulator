#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opCLC(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    clearFlag(Flags::Carry);
    ++mCyclesUsed;
}

void MOS6502::opCLD(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    clearFlag(Flags::Decimal);
    ++mCyclesUsed;
}

void MOS6502::opCLI(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    clearFlag(Flags::Interrupt);
    ++mCyclesUsed;
}

void MOS6502::opCLV(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    clearFlag(Flags::Overflow);
    ++mCyclesUsed;
}

void MOS6502::opSEC(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    setFlag(Flags::Carry);
    ++mCyclesUsed;
}

void MOS6502::opSED(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    setFlag(Flags::Decimal);
    ++mCyclesUsed;
}

void MOS6502::opSEI(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    setFlag(Flags::Interrupt);
    ++mCyclesUsed;
}

}
