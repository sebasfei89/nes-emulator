#include "./mos6502.h"

namespace nes {

void MOS6502::groupTwo_ASL(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::INVALID:
    case AddressingMode::Implied:
        break;
    case AddressingMode::Accumulator:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [&](uint8_t &operand) {
                updateFlag(Flags::Carry, operand & 0x80);
                operand <<= 1;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_ROL(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::INVALID:
    case AddressingMode::Implied:
        break;
    case AddressingMode::Accumulator:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [&](uint8_t& operand) {
                uint8_t tmp = (operand << 1) | testFlag(Flags::Carry);
                updateFlag(Flags::Carry, operand & 0x80);
                operand = tmp;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_LSR(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::INVALID:
    case AddressingMode::Implied:
        break;
    case AddressingMode::Accumulator:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [&](uint8_t& operand) {
                updateFlag(Flags::Carry, operand & 0x01);
                operand >>= 1;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_ROR(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Immediate:
    case AddressingMode::INVALID:
    case AddressingMode::Implied:
        break;
    case AddressingMode::Accumulator:
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [&](uint8_t& operand) {
                uint8_t tmp = (operand >> 1) | testFlag(Flags::Carry) << 7;
                updateFlag(Flags::Carry, operand & 0x01);
                operand = tmp;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_STX(AddressingMode addrMode) {
    if (addrMode == AddressingMode::XIndexedZeroPage)
        addrMode = AddressingMode::YIndexedZeroPage;

    switch (addrMode) {
    case AddressingMode::Immediate:
        break;
    case AddressingMode::Accumulator: // TXA_IMPLIED
        mA = mX;
        updateNZStatusFlags(mA);
        ++mCyclesUsed;
        break;
    case AddressingMode::INVALID: // 100
        break;
    case AddressingMode::Implied: // 110: TXS_IMPLIED
        mSP = mX;
        updateNZStatusFlags(mSP);
        ++mCyclesUsed;
        break;
    case AddressingMode::XIndexedAbsolute:
        break;
    case AddressingMode::Absolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::YIndexedZeroPage:
        writeResult(addrMode, mX);
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_LDX(AddressingMode addrMode) {
    if (addrMode == AddressingMode::XIndexedAbsolute)
        addrMode = AddressingMode::YIndexedAbsolute;
    else if (addrMode == AddressingMode::XIndexedZeroPage)
        addrMode = AddressingMode::YIndexedZeroPage;

    switch (addrMode) {
    case AddressingMode::Accumulator: // TAX_IMPLIED
        mX = mA;
        updateNZStatusFlags(mX);
        ++mCyclesUsed;
        break;
    case AddressingMode::Implied: // TSX_IMPLIED
        mX = mSP;
        updateNZStatusFlags(mX);
        ++mCyclesUsed;
        break;
    case AddressingMode::Immediate:
    case AddressingMode::Absolute:
    case AddressingMode::YIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::YIndexedZeroPage:
        mX = readOperand(addrMode);
        updateNZStatusFlags(mX);
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_DEC(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Accumulator: // DEX_IMPLIED
        ++mCyclesUsed;
        updateNZStatusFlags(--mX);
        break;
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [this](uint8_t& operand) {
                --operand;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

void MOS6502::groupTwo_INC(AddressingMode addrMode) {
    switch (addrMode) {
    case AddressingMode::Accumulator: // NOP_IMP
        ++mCyclesUsed;
        break;
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::ZeroPage:
    case AddressingMode::XIndexedZeroPage:
        readModifyWrite(addrMode, [this](uint8_t& operand) {
                ++operand;
                updateNZStatusFlags(operand);
                ++mCyclesUsed;
            });
        break;
    default:
        break;
    }
}

}
