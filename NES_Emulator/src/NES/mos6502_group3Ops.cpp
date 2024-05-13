#include "./mos6502.h"

#include <cassert>

namespace nes {

void MOS6502::groupThree_Default(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Implied: // CLC_IMP
        clearFlag(Flags::Carry);
        ++mCyclesUsed;
        break;
    case AddressingMode::Accumulator: // PHP_IMP
        stackPush(mStatusFlags);
        ++mCyclesUsed;
        break;
    case AddressingMode::Immediate: // BRK_IMP
        stackPush(mPC & 0x00FF);
        stackPush((mPC & 0xFF00) >> 8);
        stackPush(mStatusFlags);
        mPC = readByte(IRQ_VECTOR_ADDRESS)
            | (readByte(IRQ_VECTOR_ADDRESS + 1) << 8);
        setFlag(Flags::Break);
        ++mCyclesUsed;
        break;
    default:
        break;
    }
}

void MOS6502::groupThree_BIT(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Immediate: { // JSR_ABS
        const uint8_t addrLO = readOperand(addrMode);
        stackPush((mPC & 0xFF00) >> 8);
        stackPush((uint8_t)mPC);
        const uint8_t addrHI = readOperand(addrMode);
        mPC = addrLO | ((uint16_t)addrHI << 8);
        ++mCyclesUsed;
    } break;
    case AddressingMode::Accumulator: // PLP_IMP
        mStatusFlags = stackPull();
        mCyclesUsed += 2;
        break;
    case AddressingMode::Implied: // SEC_IMP
        setFlag(Flags::Carry);
        ++mCyclesUsed;
        break;
    case AddressingMode::Absolute: {
        const uint8_t operand = readOperand(addrMode);
        updateFlag(Flags::Negative, operand & 0x80);
        updateFlag(Flags::Overflow, operand & 0x40);
        updateFlag(Flags::Zero, !(operand & mA));
    } break;
    default:
        break;
    }
}

void MOS6502::groupThree_JMP(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Immediate: // RTI_IMPLIED
        mStatusFlags = stackPull();
        mPC = stackPull() << 8 | stackPull();
        mCyclesUsed += 2;
        break;
    case AddressingMode::Accumulator: // PHA_IMPLIED
        stackPush(mA);
        ++mCyclesUsed;
        break;
    case AddressingMode::Absolute:
        mPC = readNextByte() | ((uint16_t)readNextByte() << 8);
        break;
    case AddressingMode::Implied: // CLI_IMPLIED
        clearFlag(Flags::Interrupt);
        ++mCyclesUsed;
        break;
    default:
        break;
    }
}

void MOS6502::groupThree_JMP_IND(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Immediate: // RTS_IMP
        mPC = (stackPull() << 8 | stackPull()) + 1;
        mCyclesUsed += 3;
        break;
    case AddressingMode::Accumulator: // PLA_IMP
        mA = stackPull();
        updateNZStatusFlags(mA);
        mCyclesUsed += 2;
        break;
    case AddressingMode::Absolute:
        mPC = readNextByte() | ((uint16_t)readNextByte() << 8);
        mPC = readByte(mPC) | ((uint16_t)readByte((mPC & 0xFF00) | (uint8_t)(mPC + 1)) << 8);
        break;
    case AddressingMode::Implied: // SEI_IMP
        setFlag(Flags::Interrupt);
        ++mCyclesUsed;
        break;
    default:
        break;
    }
}

void MOS6502::groupThree_STY(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Immediate:
        break;
    case AddressingMode::Accumulator: // 010: DEY_IMP
        updateNZStatusFlags(--mY);
        ++mCyclesUsed;
        break;
    case AddressingMode::INVALID: // 100
        break;
    case AddressingMode::Implied: // 110: TYA_IMP
        mA = mY;
        updateNZStatusFlags(mA);
        ++mCyclesUsed;
        break;
    case AddressingMode::XIndexedAbsolute:
        break;
    default:
        writeResult(addrMode, mY);
        break;
    }
}

void MOS6502::groupThree_LDY(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Accumulator: // TAY_IMP
        mY = mA;
        updateNZStatusFlags(mY);
        ++mCyclesUsed;
        break;
    case AddressingMode::Implied: // CLV_IMP
        clearFlag(Flags::Overflow);
        ++mCyclesUsed;
        break;
    default:
        mY = readOperand(addrMode);
        updateNZStatusFlags(mY);
        break;
    }
}

void MOS6502::groupThree_CPY(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Implied: // CLD_IMPLIED
        clearFlag(Flags::Decimal);
        ++mCyclesUsed;
        break;
    case AddressingMode::Accumulator: // INY_IMPLIED
        updateNZStatusFlags(++mY);
        ++mCyclesUsed;
        break;
    case AddressingMode::Immediate:
    case AddressingMode::Absolute: {
        const uint8_t operand = readOperand(addrMode);
        updateFlag(Flags::Carry, operand <= mY);
        updateNZStatusFlags(mY - operand);
    } break;
    default:
        break;
    }
}

void MOS6502::groupThree_CPX(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Implied: // SED_IMPLIED
        setFlag(Flags::Decimal);
        ++mCyclesUsed;
        break;
    case AddressingMode::Accumulator: // INX_IMPLIED
        updateNZStatusFlags(++mX);
        ++mCyclesUsed;
        break;
    case AddressingMode::Immediate:
    case AddressingMode::Absolute: {
        const uint8_t operand = readOperand(addrMode);
        updateFlag(Flags::Carry, operand <= mX);
        updateNZStatusFlags(mX - operand);
    } break;
    default:
        break;
    }
}

}
