#include "./mos6502.h"

namespace nes {

void MOS6502::groupOne_ORA(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        mA |= readOperand(addrMode);
        updateNZStatusFlags(mA);
        break;
    default:
        break;
    }
}

void MOS6502::groupOne_AND(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        mA &= readOperand(addrMode);
        updateNZStatusFlags(mA);
        break;
    default:
        break;
    }
}

void MOS6502::groupOne_EOR(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        mA ^= readOperand(addrMode);
        updateNZStatusFlags(mA);
        break;
    default:
        break;
    }
}

void MOS6502::groupOne_ADC(AddressingMode addrMode) {
    switch (addrMode) {
        case AddressingMode::Immediate:
        case AddressingMode::Absolute:
        case AddressingMode::XIndexedAbsolute:
        case AddressingMode::YIndexedAbsolute: {
            const uint8_t operand = readOperand(addrMode);
            const uint16_t tmp = mA + operand + testFlag(Flags::Carry);
            updateFlag(Flags::Carry, tmp > 0xFF);
            const bool overflow = !((mA ^ operand) & 0x80) && ((mA ^ tmp) & 0x80);
            updateFlag(Flags::Overflow, overflow);
            mA = (uint8_t)(tmp & 0xFF);
            updateNZStatusFlags(mA);
        } break;
        default:
            break;
    }
}

void MOS6502::groupOne_STA(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        writeResult(addrMode, mA);
        break;
    default:
        break;
    }
}

void MOS6502::groupOne_LDA(AddressingMode addrMode) {
    switch (addrMode)
    {
    case AddressingMode::Immediate:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        mA = readOperand(addrMode);
        updateNZStatusFlags(mA);
        break;
    case AddressingMode::XIndexedZeroPageIndirect:
    case AddressingMode::ZeroPage:
    case AddressingMode::ZeroPageIndirectYIndexed:
    case AddressingMode::XIndexedZeroPage:
        break;
    default:
        break;
    }
}

void MOS6502::groupOne_CMP(AddressingMode addrMode) {
    switch (addrMode) {
        case AddressingMode::Immediate:
        case AddressingMode::Absolute:
        case AddressingMode::XIndexedAbsolute:
        case AddressingMode::YIndexedAbsolute: {
            const uint8_t operand = readOperand(addrMode);
            updateFlag(Flags::Carry, operand <= mA);
            updateNZStatusFlags(mA - operand);
        } break;
        default:
            break;
    }
}

void MOS6502::groupOne_SBC(AddressingMode addrMode) {
    switch (addrMode) {
        case AddressingMode::Immediate:
        case AddressingMode::Absolute:
        case AddressingMode::XIndexedAbsolute:
        case AddressingMode::YIndexedAbsolute: {
            const uint8_t operand = ~readOperand(addrMode);
            const uint16_t tmp = mA + operand + testBit(mStatusFlags, Flags::Carry);
            updateFlag(Flags::Carry, tmp > 0xFF);
            const bool overflow = !((mA ^ operand) & 0x80) && ((mA ^ tmp) & 0x80);
            updateFlag(Flags::Overflow, overflow);
            mA = (uint8_t)(tmp & 0xFF);
            updateNZStatusFlags(mA);
        } break;
        default:
            break;
    }
}

}
