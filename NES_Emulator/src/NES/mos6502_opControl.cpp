#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opBRK(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    stackPush(mPC & 0x00FF);
    stackPush((mPC & 0xFF00) >> 8);
    stackPush(mStatusFlags);
    mPC = readByte(IRQ_VECTOR_ADDRESS)
        | (readByte(IRQ_VECTOR_ADDRESS + 1) << 8);
    setFlag(Flags::Break);
    ++mCyclesUsed;
}

void MOS6502::opJMP(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Absolute || addrMode == AddressingMode::AbsoluteIndirect);
    mPC = getAddress(addrMode);
}

void MOS6502::opJSR(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Immediate);
    const uint8_t addrLO = readOperand(addrMode);
    stackPush((mPC & 0xFF00) >> 8);
    stackPush((uint8_t)mPC);
    const uint8_t addrHI = readOperand(addrMode);
    mPC = addrLO | ((uint16_t)addrHI << 8);
    ++mCyclesUsed;
}

void MOS6502::opRTI(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mStatusFlags = stackPull();
    mPC = stackPull() << 8 | stackPull();
    mCyclesUsed += 2;
}

void MOS6502::opRTS(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mPC = (stackPull() << 8 | stackPull()) + 1;
    mCyclesUsed += 3;
}

}
