#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opPHA(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    stackPush(mA);
    ++mCyclesUsed;
}

void MOS6502::opPHP(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    // Bit 4 (Break) is pushed as 1 for non-interrupts (eg: PHP and BRK)
    // Bit 5 (Unused) is always pushed as 1
    stackPush(mStatusFlags | 0x30);
    ++mCyclesUsed;
}

void MOS6502::opPLA(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mA = stackPull();
    updateNZStatusFlags(mA);
    mCyclesUsed += 2;
}

void MOS6502::opPLP(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    // Bit 4(Break) and bit 5(Unused) are ignored
    mStatusFlags = (stackPull() & 0xCF) | (mStatusFlags & 0x30);
    mCyclesUsed += 2;
}

}
