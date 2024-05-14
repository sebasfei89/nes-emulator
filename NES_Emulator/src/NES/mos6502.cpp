#include "./mos6502.h"
#include "./nes.h"

#include <cassert>

namespace nes {

std::array<std::array<MOS6502::InstructionFn, 8>, 3> MOS6502::sGroupInstructions = {
    std::array<MOS6502::InstructionFn, 8>{
        &MOS6502::groupThree_Default,
        &MOS6502::groupThree_BIT,
        &MOS6502::groupThree_JMP,
        &MOS6502::groupThree_JMP_IND,
        &MOS6502::groupThree_STY,
        &MOS6502::groupThree_LDY,
        &MOS6502::groupThree_CPY,
        &MOS6502::groupThree_CPX
    },
    std::array<MOS6502::InstructionFn, 8>{
        &MOS6502::groupOne_ORA,
        &MOS6502::groupOne_AND,
        &MOS6502::groupOne_EOR,
        &MOS6502::groupOne_ADC,
        &MOS6502::groupOne_STA,
        &MOS6502::groupOne_LDA,
        &MOS6502::groupOne_CMP,
        &MOS6502::groupOne_SBC
    },
    std::array<MOS6502::InstructionFn, 8>{
        &MOS6502::groupTwo_ASL,
        &MOS6502::groupTwo_ROL,
        &MOS6502::groupTwo_LSR,
        &MOS6502::groupTwo_ROR,
        &MOS6502::groupTwo_STX,
        &MOS6502::groupTwo_LDX,
        &MOS6502::groupTwo_DEC,
        &MOS6502::groupTwo_INC
    }
};

std::array<std::array<MOS6502::AddressingMode, 8>, 3> MOS6502::sGroupAddressingModes = {
    std::array<MOS6502::AddressingMode, 8>{ // Group 3
        AddressingMode::Immediate,
        AddressingMode::ZeroPage,
        AddressingMode::Accumulator, // 010
        AddressingMode::Absolute,
        AddressingMode::INVALID, // 100
        AddressingMode::XIndexedZeroPage,
        AddressingMode::Implied, // 110
        AddressingMode::XIndexedAbsolute
    },
    std::array<MOS6502::AddressingMode, 8>{ // Group 1
        AddressingMode::XIndexedZeroPageIndirect,
        AddressingMode::ZeroPage,
        AddressingMode::Immediate,
        AddressingMode::Absolute,
        AddressingMode::ZeroPageIndirectYIndexed,
        AddressingMode::XIndexedZeroPage,
        AddressingMode::YIndexedAbsolute,
        AddressingMode::XIndexedAbsolute
    },
    std::array<MOS6502::AddressingMode, 8>{ // Group 2
        AddressingMode::Immediate,
        AddressingMode::ZeroPage,
        AddressingMode::Accumulator,
        AddressingMode::Absolute,
        AddressingMode::INVALID, // 100
        AddressingMode::XIndexedZeroPage,
        AddressingMode::Implied, // 110
        AddressingMode::XIndexedAbsolute
    }
};

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
    if (addrMode == AddressingMode::Accumulator)
        return mA;

    //case AddressingMode::Immediate:
    //case AddressingMode::Absolute:
    //case AddressingMode::XIndexedAbsolute:
    //case AddressingMode::YIndexedAbsolute:
    return readByte(getAddress(addrMode));
}

void MOS6502::writeResult(AddressingMode addrMode, uint8_t value)
{
    switch (addrMode) {
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute:
    case AddressingMode::YIndexedAbsolute:
        writeByte(getAddress(addrMode, true), value);
        break;
    default:
        break;
    }
}

void MOS6502::readModifyWrite(AddressingMode addrMode, std::function<void(uint8_t &value)> updateFn)
{
    switch (addrMode) {
    case AddressingMode::Accumulator:
        updateFn(mA);
        break;
    case AddressingMode::Absolute:
    case AddressingMode::XIndexedAbsolute: {
        const uint16_t addr = getAddress(addrMode, true);
        uint8_t value = readByte(addr);
        updateFn(value);
        writeByte(addr, value);
    } break;
    default:
        break;
    }
}

uint16_t MOS6502::getAddress(AddressingMode addrMode, bool write) {
    switch (addrMode) {
    case AddressingMode::Accumulator:
        assert(false);
        break;
    case AddressingMode::Immediate:
        return mPC++;
    case AddressingMode::Absolute:
        return readNextByte() | (readNextByte() << 8);
    case AddressingMode::XIndexedAbsolute: {
        const uint16_t effectiveAddr = (readNextByte() | (readNextByte() << 8));
        if (write || ((effectiveAddr & 0x00FF) + mX > 0x00FF))
            ++mCyclesUsed;
        return effectiveAddr + mX;
    }
    case AddressingMode::YIndexedAbsolute: {
        const uint16_t effectiveAddr = (readNextByte() | (readNextByte() << 8));
        if (write || ((effectiveAddr & 0x00FF) + mY > 0x00FF))
            ++mCyclesUsed;
        return effectiveAddr + mY;
    }
    }

    return 0x0000;
}

void MOS6502::runInstruction() {
    mCyclesUsed = 0;
    const uint8_t instruction = readNextByte();

    const uint8_t aaa = ((uint8_t)instruction & 0b1110'0000) >> 5; // OP code from group
    const uint8_t bbb = ((uint8_t)instruction & 0b0001'1100) >> 2; // Addressing mode
    const uint8_t cc =  ((uint8_t)instruction & 0b0000'0011) >> 0; // Group
    if (cc == 0x01) // Group one
    {
        (this->*sGroupInstructions[cc][aaa])(sGroupAddressingModes[cc][bbb]);
    }
    else if (cc == 0x02) // Group two
    {
        (this->*sGroupInstructions[cc][aaa])(sGroupAddressingModes[cc][bbb]);
    }
    else if (cc == 0x00) // Group three
    {
        (this->*sGroupInstructions[cc][aaa])(sGroupAddressingModes[cc][bbb]);
    }
    else { // (((uint8_t)instruction & 0x03) == 0x03)
        return; // Undocumented instructions
    }
}

}
