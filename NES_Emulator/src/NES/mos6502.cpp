#include "./mos6502.h"
#include "./nes.h"

#include <cassert>

namespace nes {

#define OP(FN, AM) InstructionTableEntry{&op##FN, AddressingMode::AM}
std::array<MOS6502::InstructionGroup, 3> MOS6502::sInstructionGroups = {
    InstructionGroup{
        InstructionTableRow{ OP(BRK, Implied  ), OP(NOP, ZeroPage), OP(PHP, Implied), OP(NOP, Absolute        ), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(CLC, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(JSR, Immediate), OP(BIT, ZeroPage), OP(PLP, Implied), OP(BIT, Absolute        ), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(SEC, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(RTI, Implied  ), OP(NOP, ZeroPage), OP(PHA, Implied), OP(JMP, Absolute        ), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(CLI, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(RTS, Implied  ), OP(NOP, ZeroPage), OP(PLA, Implied), OP(JMP, AbsoluteIndirect), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(SEI, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(STY, ZeroPage), OP(DEY, Implied), OP(STY, Absolute        ), OP(NOP, Implied), OP(STY, XIndexedZeroPage), OP(TYA, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(LDY, Immediate), OP(LDY, ZeroPage), OP(TAY, Implied), OP(LDY, Absolute        ), OP(NOP, Implied), OP(LDY, XIndexedZeroPage), OP(CLV, Implied), OP(LDY, XIndexedAbsolute) },
        InstructionTableRow{ OP(CPY, Immediate), OP(CPY, ZeroPage), OP(INY, Implied), OP(CPY, Absolute        ), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(CLD, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(CPX, Immediate), OP(CPX, ZeroPage), OP(INX, Implied), OP(CPX, Absolute        ), OP(NOP, Implied), OP(NOP, XIndexedZeroPage), OP(SED, Implied), OP(NOP, XIndexedAbsolute) }
    },
    InstructionGroup{
        InstructionTableRow{ OP(ORA, XIndexedZeroPageIndirect), OP(ORA, ZeroPage), OP(ORA, Immediate), OP(ORA, Absolute), OP(ORA, ZeroPageIndirectYIndexed), OP(ORA, XIndexedZeroPage), OP(ORA, YIndexedAbsolute), OP(ORA, XIndexedAbsolute) },
        InstructionTableRow{ OP(AND, XIndexedZeroPageIndirect), OP(AND, ZeroPage), OP(AND, Immediate), OP(AND, Absolute), OP(AND, ZeroPageIndirectYIndexed), OP(AND, XIndexedZeroPage), OP(AND, YIndexedAbsolute), OP(AND, XIndexedAbsolute) },
        InstructionTableRow{ OP(EOR, XIndexedZeroPageIndirect), OP(EOR, ZeroPage), OP(EOR, Immediate), OP(EOR, Absolute), OP(EOR, ZeroPageIndirectYIndexed), OP(EOR, XIndexedZeroPage), OP(EOR, YIndexedAbsolute), OP(EOR, XIndexedAbsolute) },
        InstructionTableRow{ OP(ADC, XIndexedZeroPageIndirect), OP(ADC, ZeroPage), OP(ADC, Immediate), OP(ADC, Absolute), OP(ADC, ZeroPageIndirectYIndexed), OP(ADC, XIndexedZeroPage), OP(ADC, YIndexedAbsolute), OP(ADC, XIndexedAbsolute) },
        InstructionTableRow{ OP(STA, XIndexedZeroPageIndirect), OP(STA, ZeroPage), OP(NOP, Immediate), OP(STA, Absolute), OP(STA, ZeroPageIndirectYIndexed), OP(STA, XIndexedZeroPage), OP(STA, YIndexedAbsolute), OP(STA, XIndexedAbsolute) },
        InstructionTableRow{ OP(LDA, XIndexedZeroPageIndirect), OP(LDA, ZeroPage), OP(LDA, Immediate), OP(LDA, Absolute), OP(LDA, ZeroPageIndirectYIndexed), OP(LDA, XIndexedZeroPage), OP(LDA, YIndexedAbsolute), OP(LDA, XIndexedAbsolute) },
        InstructionTableRow{ OP(CMP, XIndexedZeroPageIndirect), OP(CMP, ZeroPage), OP(CMP, Immediate), OP(CMP, Absolute), OP(CMP, ZeroPageIndirectYIndexed), OP(CMP, XIndexedZeroPage), OP(CMP, YIndexedAbsolute), OP(CMP, XIndexedAbsolute) },
        InstructionTableRow{ OP(SBC, XIndexedZeroPageIndirect), OP(SBC, ZeroPage), OP(SBC, Immediate), OP(SBC, Absolute), OP(SBC, ZeroPageIndirectYIndexed), OP(SBC, XIndexedZeroPage), OP(SBC, YIndexedAbsolute), OP(SBC, XIndexedAbsolute) }
    },
    InstructionGroup{
        InstructionTableRow{ OP(NOP, Immediate), OP(ASL, ZeroPage), OP(ASL, Accumulator), OP(ASL, Absolute), OP(NOP, Implied), OP(ASL, XIndexedZeroPage), OP(NOP, Implied), OP(ASL, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(ROL, ZeroPage), OP(ROL, Accumulator), OP(ROL, Absolute), OP(NOP, Implied), OP(ROL, XIndexedZeroPage), OP(NOP, Implied), OP(ROL, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(LSR, ZeroPage), OP(LSR, Accumulator), OP(LSR, Absolute), OP(NOP, Implied), OP(LSR, XIndexedZeroPage), OP(NOP, Implied), OP(LSR, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(ROR, ZeroPage), OP(ROR, Accumulator), OP(ROR, Absolute), OP(NOP, Implied), OP(ROR, XIndexedZeroPage), OP(NOP, Implied), OP(ROR, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(STX, ZeroPage), OP(TXA, Implied    ), OP(STX, Absolute), OP(NOP, Implied), OP(STX, YIndexedZeroPage), OP(TXS, Implied), OP(NOP, XIndexedAbsolute) },
        InstructionTableRow{ OP(LDX, Immediate), OP(LDX, ZeroPage), OP(TAX, Implied    ), OP(LDX, Absolute), OP(NOP, Implied), OP(LDX, YIndexedZeroPage), OP(TSX, Implied), OP(LDX, YIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(DEC, ZeroPage), OP(DEX, Implied    ), OP(DEC, Absolute), OP(NOP, Implied), OP(DEC, XIndexedZeroPage), OP(NOP, Implied), OP(DEC, XIndexedAbsolute) },
        InstructionTableRow{ OP(NOP, Immediate), OP(INC, ZeroPage), OP(NOP, Implied    ), OP(INC, Absolute), OP(NOP, Implied), OP(INC, XIndexedZeroPage), OP(NOP, Implied), OP(INC, XIndexedAbsolute) }
    }
};
#undef OP

void MOS6502::reset() {
    mPC = mBus->read(RESET_ADDRESS) | (mBus->read(RESET_ADDRESS + 1) << 8);
    mSP = 0xFF;
    mStatusFlags = mA = mX = mY = 0x00;
    mRam.reset();
}

size_t MOS6502::run(size_t numCycles) {
    size_t totalCyclesUsed = 0;
    while (totalCyclesUsed < numCycles) {
        runInstruction();
        totalCyclesUsed += mCyclesUsed;
    }
    return totalCyclesUsed;
}

uint8_t MOS6502::readByte(uint16_t address) {
    ++mCyclesUsed;
    return mBus->read(address);
}

void MOS6502::writeByte(uint16_t address, uint8_t data) {
    ++mCyclesUsed;
    mBus->write(address, data);
}

uint8_t MOS6502::readOperand(AddressingMode addrMode)
{
    return (addrMode == AddressingMode::Accumulator) ? mA : readByte(getAddress(addrMode));
}

void MOS6502::writeResult(AddressingMode addrMode, uint8_t value)
{
    // Absolute, XIndexedAbsolute, YIndexedAbsolute
    // ZeroPage, XIndexedZeroPage, YIndexedZeroPage, XIndexedZeroPageIndirect
    writeByte(getAddress(addrMode, true), value);
}

void MOS6502::readModifyWrite(AddressingMode addrMode, UpdateFn updateFn)
{
    if (addrMode == AddressingMode::Accumulator) {
        mA = updateFn(mA);
    }
    else {
        // Absolute, XIndexedAbsolute, ZeroPage, XIndexedZeroPage
        const uint16_t addr = getAddress(addrMode, true);
        writeByte(addr, updateFn(readByte(addr)));
    }
    ++mCyclesUsed;
}

uint16_t MOS6502::getAddress(AddressingMode addrMode, bool write) {
    switch (addrMode) {
        case AddressingMode::Immediate:                               return mPC++;
        case AddressingMode::Absolute:                                return readAddressAbs();
        case AddressingMode::AbsoluteIndirect:                        return readAddressInd(readAddressAbs());
        case AddressingMode::XIndexedAbsolute:                        return handlePageCross(readAddressAbs(), mX, write);
        case AddressingMode::YIndexedAbsolute:                        return handlePageCross(readAddressAbs(), mY, write);
        case AddressingMode::ZeroPage:                                return readNextByte();
        case AddressingMode::XIndexedZeroPage:         ++mCyclesUsed; return (uint8_t)(readNextByte() + mX);
        case AddressingMode::YIndexedZeroPage:         ++mCyclesUsed; return (uint8_t)(readNextByte() + mY);
        case AddressingMode::XIndexedZeroPageIndirect: ++mCyclesUsed; return readAddressInd((uint8_t)(readNextByte() + mX));
        case AddressingMode::ZeroPageIndirectYIndexed:                return handlePageCross(readAddressInd(readNextByte()), mY, write);
        default: break;
    }

    assert(false);
    return 0x0000;
}

void MOS6502::runInstruction() {
    mCyclesUsed = 0;
    const uint8_t instruction = readNextByte(); // aaabbbcc
    const uint8_t aaa = ((uint8_t)instruction & 0b1110'0000) >> 5; // OP code from group
    const uint8_t bbb = ((uint8_t)instruction & 0b0001'1100) >> 2; // Addressing mode
    const uint8_t cc =  ((uint8_t)instruction & 0b0000'0011) >> 0; // Group
    if (cc != 0x03) {
        const InstructionTableEntry &entry = sInstructionGroups[cc][aaa][bbb];
        (this->*entry.op)(entry.addrMode);
    }
    else {
        // Undocumented instructions
        ++mCyclesUsed;
    }
}

}
