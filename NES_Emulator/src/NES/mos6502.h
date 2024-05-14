#pragma once

#include "./ram.h"
#include "./util.h"

#include <array>
#include <functional>

struct NESTest;

namespace nes {

class Bus;

class MOS6502 {
public:
    enum class AddressingMode : uint8_t {
        // 1 Byte
        Implied, Accumulator,
        // 2 Bytes
        Immediate, Relative,
        ZeroPage, XIndexedZeroPage, YIndexedZeroPage,
        XIndexedZeroPageIndirect, ZeroPageIndirectYIndexed,
        // 3 Bytes
        Absolute, XIndexedAbsolute, YIndexedAbsolute, AbsoluteIndirect,
        INVALID
    };

    enum Flags : uint8_t {
        Carry = 0,
        Zero = 1,
        Interrupt = 2,
        Decimal = 3,
        Break = 4,
        Unused = 5,
        Overflow = 6,
        Negative = 7
    };

    void reset();
    size_t run(size_t numCycles);

    uint8_t statusFlags() const { return mStatusFlags; }
    uint16_t programCounter() const { return mPC; }
    uint8_t stackPointer() const { return mSP; }

    uint8_t accumulator() const { return mA; }
    uint8_t xRegister() const { return mX; }
    uint8_t yRegister() const { return mY; }

    const Ram<2048>& ram() const { return mRam; }
    Ram<2048>& ram() { return mRam; }

private:
    // Read/Write to bus
    uint8_t readNextByte() { return readByte(mPC++); }  // Consumes 1 cycle
    uint8_t readByte(uint16_t address);                 // Consumes 1 cycle
    void writeByte(uint16_t address, uint8_t data);     // Consumes 1 cycle

    // Pull/Push to stack
    void stackPush(uint8_t value) { writeByte(0x0100 | mSP--, value); } // Consumes 1 cycle
    uint8_t stackPull() { return readByte(0x0100 | ++mSP); }            // Consumes 1 cycle

    // Read operand using addressing mode
    uint8_t readOperand(AddressingMode addrMode);
    void writeResult(AddressingMode addrMode, uint8_t value);
    void readModifyWrite(AddressingMode addrMode, std::function<void(uint8_t &value)> lambda);

    // Addressing modes
    uint16_t getAddress(AddressingMode addrMode, bool write=false);

    void runInstruction();

    void updateNZStatusFlags(uint8_t value) {
        updateBit(mStatusFlags, Flags::Zero, !value);
        updateBit(mStatusFlags, Flags::Negative, value & 0x80);
    }

    friend class Bus;
    void onConnect(Bus* bus) { mBus = bus; }
    void onDisconnect() { mBus = nullptr; }

    uint8_t testFlag(Flags flag) const { return testBit(mStatusFlags, Flags::Carry); }
    void setFlag(Flags flag) { setBit(mStatusFlags, flag); }
    void clearFlag(Flags flag) { clearBit(mStatusFlags, flag); }
    void updateFlag(Flags flag, bool set) { updateBit(mStatusFlags, flag, set); }

    // Group-one instructions
    void groupOne_ORA(AddressingMode addrMode);
    void groupOne_AND(AddressingMode addrMode);
    void groupOne_EOR(AddressingMode addrMode);
    void groupOne_ADC(AddressingMode addrMode);
    void groupOne_STA(AddressingMode addrMode);
    void groupOne_LDA(AddressingMode addrMode);
    void groupOne_CMP(AddressingMode addrMode);
    void groupOne_SBC(AddressingMode addrMode);

    // Group-two instructions
    void groupTwo_ASL(AddressingMode addrMode);
    void groupTwo_ROL(AddressingMode addrMode);
    void groupTwo_LSR(AddressingMode addrMode);
    void groupTwo_ROR(AddressingMode addrMode);
    void groupTwo_STX(AddressingMode addrMode);
    void groupTwo_LDX(AddressingMode addrMode);
    void groupTwo_DEC(AddressingMode addrMode);
    void groupTwo_INC(AddressingMode addrMode);

    // Group-three instructions
    void groupThree_Default(AddressingMode addrMode);
    void groupThree_BIT(AddressingMode addrMode);
    void groupThree_JMP(AddressingMode addrMode);
    void groupThree_JMP_IND(AddressingMode addrMode);
    void groupThree_STY(AddressingMode addrMode);
    void groupThree_LDY(AddressingMode addrMode);
    void groupThree_CPY(AddressingMode addrMode);
    void groupThree_CPX(AddressingMode addrMode);

private:
    friend NESTest;

    size_t mCyclesUsed; // Cycles consumed by last instruction ran
    uint16_t mPC; // Program counter
    uint8_t mSP; // Stack pointer
    uint8_t mStatusFlags;
    uint8_t mA; // Accumulator registry
    uint8_t mX; // X registry
    uint8_t mY; // Y registry

    Bus* mBus;
    Ram<2048> mRam; // 2KB of internal RAM [$0000-$07FF]

private:
    using InstructionFn = void(MOS6502::*)(AddressingMode);
    static std::array<std::array<InstructionFn, 8>, 3> sGroupInstructions;
    static std::array<std::array<AddressingMode, 8>, 3> sGroupAddressingModes;
};

}
