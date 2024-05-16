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
    stackPush(mStatusFlags);
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
    mStatusFlags = stackPull();
    mCyclesUsed += 2;
}

}
