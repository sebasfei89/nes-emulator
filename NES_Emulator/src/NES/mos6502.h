#pragma once

#include "./bus.h"
#include "./ram.h"
#include "./util.h"

#include <array>
#include <functional>

// 6502 microprocessor (https://www.nesdev.org/obelisk-6502-guide/architecture.html):
//      Little-endian 8 bit CPU with 16 bit address bus capable of addressing 64 Kb of memory

// NES memory map
//      ============== 2KB internal RAM ===============
//      [$0000-$00FF] Zero Page memory
//      [$0100-$01FF] Second page is reserved for the system stack and cannot be relocated
//      [$0200-$07FF] Remainig of 2 KB internal ram
//      -----------------------------------------------
//      [$0800-$1FFF] 3 mirrors of [$0000-$07FF]
//      ===================== PPU =====================
//      [$2000-$2007] PPU registers
//      -----------------------------------------------
//      [$2008-$3FFF] mirrors of [$2000-$2007]
//      ================== APU / IO ===================
//      [$4000-$4017] NES APU and I/O registers
//      [$4018-$401F] APU and I/O funcs normally disabled
//      ================== CARTRIDGE ==================
//      [$4020-$5FFF] Unmapped. Available for cartridge use
//      [$6000-$7FFF] Usually cartridge ram
//      [$8000-$FFF9] Usually cartridge rom and mapper registers
//      -----------------------------------------------
//      [$FFFA-$FFFB] Reserved for NMI handler address
//      [$FFFC-$FFFD] Program startup address
//      [$FFFE-$FFFF] BRK/interrupt request hanndler
//      ===============================================

// Registers (https://www.nesdev.org/obelisk-6502-guide/registers.html):
// Program Counter [16]: points to the next instruction to be executed
// Stack Pointer    [8]: points to the next free location in the stack (stack overflow is unchecked by the cpu, may crash the program)
// Accumulator      [8]: used by arithmetic and logical operation
// X & Y registers  [8]: both used for counters or offsets for accessing memory
// Processor Status [8]:
//      [0] Carry: signal overflow/underflow durint arithmetic/comparisson or logical shifts operations or explicitly set by SEC/CLC instructions
//      [1] Zero: zet if result of last operation was zero
//      [2] Interrupt disable: set by SEI/CLI instructions
//      [3] Decimal mode: Enable BCD arithmetic during addition and subtraction. Set by SED/CLD instructions
//      [4] Break command: Set when a BRK instruction has been executed and an interrupt has been generated to process it.
//      [5] Unused
//      [6] Overflow
//      [7] Negative

// Instructions: see https://www.pagetable.com/c64ref/6502/?tab=2

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
        Absolute, XIndexedAbsolute, YIndexedAbsolute, AbsoluteIndirect
    };

    enum class Flags : uint8_t {
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
    void runFromAddress(uint16_t addr);

    uint16_t runTillInfiniteLoop(uint16_t addr, size_t& cyclesUsed);

    uint8_t statusFlags() const { return mStatusFlags; }
    uint16_t programCounter() const { return mPC; }
    uint8_t stackPointer() const { return mSP; }

    uint8_t accumulator() const { return mA; }
    uint8_t xRegister() const { return mX; }
    uint8_t yRegister() const { return mY; }

    Bus& bus() { return mBus; }

private:
    // Read from bus
    uint8_t readNextByte() { return readByte(mPC++); }  // Consumes 1 cycle
    uint8_t readByte(uint16_t address);                 // Consumes 1 cycle
    uint16_t readAddressAbs() { return (readNextByte() | (readNextByte() << 8)); } // Consumes 2 cycle
    uint16_t readAddressInd(uint16_t baseAddr) { return (readByte(baseAddr) | (readByte((baseAddr & 0xFF00) | (uint8_t)(baseAddr + 1)) << 8)); } // Consumes 2 cycle

    // Write to bus
    void writeByte(uint16_t address, uint8_t data);     // Consumes 1 cycle

    // Pull/Push to stack
    void stackPush(uint8_t value) { writeByte(0x0100 | mSP--, value); } // Consumes 1 cycle
    uint8_t stackPull() { return readByte(0x0100 | ++mSP); }            // Consumes 1 cycle

    // Read operand using addressing mode
    uint8_t readOperand(AddressingMode addrMode);
    void writeResult(AddressingMode addrMode, uint8_t value);
    using UpdateFn = std::function<uint8_t(uint8_t value)>;
    void readModifyWrite(AddressingMode addrMode, UpdateFn lambda);

    // Addressing modes
    uint16_t getAddress(AddressingMode addrMode, bool write=false);
    uint16_t handlePageCross(uint16_t baseAddr, uint8_t offset, bool isWrite) {
        const uint16_t effectiveAddr = baseAddr + offset;
        if (isWrite || (baseAddr ^ effectiveAddr) >> 8)
            ++mCyclesUsed;
        return effectiveAddr;
    }

    void runInstruction();

    void updateNZStatusFlags(uint8_t value) {
        updateBit(mStatusFlags, (uint8_t)Flags::Zero, !value);
        updateBit(mStatusFlags, (uint8_t)Flags::Negative, value & 0x80);
    }

    uint8_t testFlag(Flags flag) const { return testBit(mStatusFlags, (uint8_t)flag); }
    void setFlag(Flags flag) { setBit(mStatusFlags, (uint8_t)flag); }
    void clearFlag(Flags flag) { clearBit(mStatusFlags, (uint8_t)flag); }
    void updateFlag(Flags flag, bool set) { updateBit(mStatusFlags, (uint8_t)flag, set); }

    void opNOP(AddressingMode addrMode) { ++mCyclesUsed; }
    void opBranchIf(AddressingMode addrMode, Flags flag, uint8_t set);

#define OP(CODE) void op##CODE(AddressingMode addrMode);
    OP(LDA) OP(LDX) OP(LDY) OP(STA) OP(STX) OP(STY) // Load/Store
    OP(TAX) OP(TAY) OP(TSX) OP(TXA) OP(TXS) OP(TYA) // Transfer
    OP(PHA) OP(PHP) OP(PLA) OP(PLP) // Stack
    OP(ASL) OP(LSR) OP(ROL) OP(ROR) // Shift
    OP(AND) OP(BIT) OP(EOR) OP(ORA) // Logic
    OP(ADC) OP(CMP) OP(CPX) OP(CPY) OP(SBC) // Arithmetic
    OP(DEC) OP(DEX) OP(DEY) OP(INC) OP(INX) OP(INY) // Dec/Inc
    OP(BRK) OP(JMP) OP(JSR) OP(RTI) OP(RTS) // Control
    OP(BCC) OP(BCS) OP(BEQ) OP(BMI) OP(BNE) OP(BPL) OP(BVC) OP(BVS) // Branch
    OP(CLC) OP(CLD) OP(CLI) OP(CLV) OP(SEC) OP(SED) OP(SEI) // Flags
#undef OP

private:
    friend NESTest;

    size_t mCyclesUsed; // Cycles consumed by last instruction ran
    uint16_t mPC; // Program counter
    uint8_t mSP; // Stack pointer
    uint8_t mStatusFlags;
    uint8_t mA; // Accumulator registry
    uint8_t mX; // X registry
    uint8_t mY; // Y registry

    Bus mBus;

private:
    struct InstructionTableEntry {
        void(MOS6502::*op)(AddressingMode);
        AddressingMode addrMode;
    };

    using InstructionTableRow = std::array<InstructionTableEntry, 8>;
    using InstructionGroup = std::array<InstructionTableRow, 8>;
    static std::array<InstructionGroup, 3> sInstructionGroups;
};

}
