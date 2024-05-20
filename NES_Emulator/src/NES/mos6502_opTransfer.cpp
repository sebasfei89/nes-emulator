#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opTXA(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mA = mX;
    updateNZStatusFlags(mA);
    ++mCyclesUsed;
}

void MOS6502::opTYA(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mA = mY;
    updateNZStatusFlags(mA);
    ++mCyclesUsed;
}

void MOS6502::opTXS(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mSP = mX;
    ++mCyclesUsed;
}

void MOS6502::opTAX(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mX = mA;
    updateNZStatusFlags(mX);
    ++mCyclesUsed;
}

void MOS6502::opTAY(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mY = mA;
    updateNZStatusFlags(mY);
    ++mCyclesUsed;
}

void MOS6502::opTSX(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mX = mSP;
    updateNZStatusFlags(mX);
    ++mCyclesUsed;
}

}
