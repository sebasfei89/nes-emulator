#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::opBRK(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    readOperand(AddressingMode::Immediate); // Read & disscard next byte
    stackPush((mPC & 0xFF00) >> 8);
    stackPush(mPC & 0x00FF);
    // Bit 4 (Break) is pushed as 1 for non-interrupts (eg: PHP and BRK)
    // Bit 5 (Unused) is always pushed as 1
    stackPush(mStatusFlags | 0x30);
    mPC = readByte(IRQ_VECTOR_ADDRESS)
        | (readByte(IRQ_VECTOR_ADDRESS + 1) << 8);
    setFlag(Flags::Interrupt);
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
    // Bit 4(Break) and bit 5(Unused) are ignored
    mStatusFlags = (stackPull() & 0xCF) | (mStatusFlags & 0x30);
    mPC = stackPull() | (stackPull() << 8);
    mCyclesUsed += 2;
}

void MOS6502::opRTS(AddressingMode addrMode) {
    assert(addrMode == AddressingMode::Implied);
    mPC = (stackPull() | (stackPull() << 8)) + 1;
    mCyclesUsed += 3;
}

}
