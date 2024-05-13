#pragma once

#include "./mos6502.h"
#include "./ram.h"
#include "./util.h"

#include <memory>
#include <span>

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

namespace nes {

class MOS6502;
class Bus;

class Cartridge {
public:
    uint8_t read(uint16_t addr) const { return mRam.mData[addr - CARTRIDGE_INIT_ADDRESS]; }
    void write(uint16_t addr, uint8_t data) { mRam.mData[addr - CARTRIDGE_INIT_ADDRESS] = data; }

    void load(uint16_t startAddr, std::span<const uint8_t> bytes) {
        std::memcpy(&mRam.mData[startAddr - CARTRIDGE_INIT_ADDRESS], bytes.data(), bytes.size_bytes());
    }

private:
    friend Bus;
    void onConnect(Bus* bus) { mBus = bus; }
    void onDisconnect() { mBus = nullptr; }

private:
    Bus* mBus = nullptr;
    // 8160 B  UNMAPPED     [$4020-$5FFF]
    // 8192 B  Internal RAM [$6000-$7FFF]
    //   32 KB Internal ROM [$8000-$FFF9]
    //    2 B  NMI Handler      [$FFFA/B]
    //    2 B  Reset            [$FFFC/D]
    //    2 B  IRQ Handler      [$FFFE/F]
    Ram<49120> mRam;
};

class Bus {
public:
    ~Bus() {
        connect(std::shared_ptr<MOS6502>());
        connect(std::shared_ptr<Cartridge>());
    }

    void connect(std::shared_ptr<MOS6502> cpu);
    void connect(std::shared_ptr<Cartridge> cartridge);

    uint8_t read(uint16_t addr) const {
        if (addr >= CARTRIDGE_INIT_ADDRESS) {
            return mCartridge->read(addr);
        }
        else if (addr < PPU_REGISTERS_ADDRESS) {
            return mCpu->ram().mData[addr & 0x07FF];
        }

        return 0xFE;
    }

    void write(uint16_t addr, uint8_t data) {
        if (addr < PPU_REGISTERS_ADDRESS) {
            mCpu->ram().mData[addr & 0x07FF] = data;
        }
    }

private:
    std::shared_ptr<MOS6502> mCpu;
    std::shared_ptr<Cartridge> mCartridge;
};

}
