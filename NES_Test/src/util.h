#pragma once

#include "NES/nes.h"
#include "NES/opCodes.h"

#include <Catch2/catch.hpp>

namespace OP = nes::opcode;

enum class OPAddr : uint8_t {
    // Register addressing:
    Acc, X, Y, PC_HI, PC_LO, SP,
    // Memory addressing:
    MemABS, MemABS_1, // Absolute
    MemABS_IND, // Absolute Indirect with page cross
    MemZeroPage, MemZeroPage_1, // Zero Page
    MemIRQ_HI, MemIRQ_LO, // IRQ vector
    MemSTK_0, MemSTK_1, MemSTK_2, // Stack
};

struct OPAddrInitializer {
    OPAddr addr;
    uint8_t value;
};

struct NESTest
{
    static constexpr uint16_t CPU_ZERO_PAGE_ADDRESS = 0x0000;
    static constexpr uint16_t CPU_ABSOLUTE_ADDRESS = 0x0200;
    static constexpr uint16_t CPU_ABSOLUTE_ADDRESS_WITH_PAGE_CROSS = 0x02FF;
    static constexpr uint16_t PROGRAM_STARTUP_ADDR = 0x8000;

    NESTest()
	{
        cpu = std::make_shared<nes::MOS6502>();
        memset(cpu.get(), 0xFE, sizeof(nes::MOS6502));

        cart = std::make_shared<nes::Cartridge>();
        uint8_t cartData[]{ nes::loByte(PROGRAM_STARTUP_ADDR), nes::hiByte(PROGRAM_STARTUP_ADDR) };
        cart->load(nes::RESET_ADDRESS, std::span{ cartData });

        bus.connect(cpu);
        bus.connect(cart);
	}

    void loadAndReset(const std::vector<uint8_t> &prog) {
        cart->load(PROGRAM_STARTUP_ADDR, std::span{ prog.data(), prog.size() });
        cpu->reset();
    }

    void setFlags(uint8_t flags) { cpu->mStatusFlags = flags; }
    void setFlag(nes::MOS6502::Flags flag) { cpu->setFlag(flag); }
    void clearFlag(nes::MOS6502::Flags flag) { cpu->clearFlag(flag); }

    uint8_t cpuRegister(OPAddr addr) const {
        switch (addr)
        {
        case OPAddr::Acc: return cpu->accumulator();
        case OPAddr::X: return cpu->xRegister();
        case OPAddr::Y: return cpu->yRegister();
        default:
            assert(false);
            break;
        }
        return 0x00;
    }

    void setCpuRegister(OPAddr reg, uint8_t value) {
        switch (reg)
        {
            case OPAddr::Acc:
                setAccumuluator(value);
                break;
            case OPAddr::X:
                setRegisterX(value);
                break;
            case OPAddr::Y:
                setRegisterY(value);
                break;
            default:
                assert(false);
                break;
        }
    }

    void setStackPointer(uint8_t data) { cpu->mSP = data; }
    void setAccumuluator(uint8_t data) { cpu->mA = data; }
    void setRegisterX(uint8_t data) { cpu->mX = data; }
    void setRegisterY(uint8_t data) { cpu->mY = data; }

    uint8_t &cpuRam(uint16_t addr) const { return cpu->ram().mData[addr]; }
    void writeCart(uint16_t addr, uint8_t value) const { return cart->write(addr, value); }

    uint8_t read(OPAddr addr) {
        switch (addr)
        {
        case OPAddr::Acc: return cpu->mA;
        case OPAddr::X:  return cpu->mX;
        case OPAddr::Y:  return cpu->mY;
        case OPAddr::PC_HI:  return cpu->mPC >> 8;
        case OPAddr::PC_LO:  return cpu->mPC & 0x00FF;
        case OPAddr::SP:  return cpu->mSP;
        case OPAddr::MemABS: return cpuRam(CPU_ABSOLUTE_ADDRESS);
        case OPAddr::MemABS_1: return cpuRam(CPU_ABSOLUTE_ADDRESS+1);
        case OPAddr::MemABS_IND: return cpuRam(CPU_ABSOLUTE_ADDRESS_WITH_PAGE_CROSS);
        case OPAddr::MemZeroPage: return cpuRam(CPU_ZERO_PAGE_ADDRESS);
        case OPAddr::MemZeroPage_1: return cpuRam(CPU_ZERO_PAGE_ADDRESS+1);
        case OPAddr::MemSTK_0: return cpuRam(nes::STACK_ADDRESS);
        case OPAddr::MemSTK_1: return cpuRam(nes::STACK_ADDRESS-1);
        case OPAddr::MemSTK_2: return cpuRam(nes::STACK_ADDRESS-2);
        default:
            assert(false);
            break;
        }
        return 0;
    }

    void write(OPAddr addr, uint8_t value) {
        switch (addr)
        {
        case OPAddr::Acc:
            setAccumuluator(value);
            break;
        case OPAddr::X:
            setRegisterX(value);
            break;
        case OPAddr::Y:
            setRegisterY(value);
            break;
        case OPAddr::SP:
            setStackPointer(value);
            break;
        case OPAddr::MemABS:
            cpuRam(CPU_ABSOLUTE_ADDRESS) = value;
            break;
        case OPAddr::MemABS_1:
            cpuRam(CPU_ABSOLUTE_ADDRESS+1) = value;
            break;
        case OPAddr::MemABS_IND:
            cpuRam(CPU_ABSOLUTE_ADDRESS_WITH_PAGE_CROSS) = value;
            break;
        case OPAddr::MemZeroPage:
            cpuRam(CPU_ZERO_PAGE_ADDRESS) = value;
            break;
        case OPAddr::MemZeroPage_1:
            cpuRam(CPU_ZERO_PAGE_ADDRESS + 1) = value;
            break;
        case OPAddr::MemIRQ_LO:
            writeCart(nes::IRQ_VECTOR_ADDRESS, value);
            break;
        case OPAddr::MemIRQ_HI:
            writeCart(nes::IRQ_VECTOR_ADDRESS+1, value);
            break;
        case OPAddr::MemSTK_0:
            cpuRam(nes::STACK_ADDRESS) = value;
            break;
        case OPAddr::MemSTK_1:
            cpuRam(nes::STACK_ADDRESS - 1) = value;
            break;
        case OPAddr::MemSTK_2:
            cpuRam(nes::STACK_ADDRESS - 2) = value;
            break;
        default:
            assert(false);
            break;
        }
    }

    void testProgram(const char* prgDesc, const std::vector<uint8_t>& prg, uint8_t expectedCycles,
        OPAddr loadAddr, uint8_t initialValue, uint8_t initialFlags,
        OPAddr storeAddr, uint8_t expectedValue, uint8_t expectedFlags)
    {
        testProgram(prgDesc, prg, expectedCycles, {{loadAddr, initialValue}}, initialFlags, {{storeAddr, expectedValue}}, expectedFlags);
    }

    void testProgram(const char* prgDesc, const std::vector<uint8_t>& prg, uint8_t expectedCycles,
        const std::vector<OPAddrInitializer>& initialValues, uint8_t initialFlags,
        OPAddr storeAddr, uint8_t expectedValue, uint8_t expectedFlags)
    {
        testProgram(prgDesc, prg, expectedCycles, initialValues, initialFlags, {{storeAddr, expectedValue}}, expectedFlags);
    }
    
    void testProgram(const char* prgDesc, const std::vector<uint8_t>& prg, uint8_t expectedCycles,
        OPAddr loadAddr, uint8_t initialValue, uint8_t initialFlags,
        const std::vector<OPAddrInitializer> &expectedValues, uint8_t expectedFlags)
    {
        testProgram(prgDesc, prg, expectedCycles, { {loadAddr, initialValue} }, initialFlags, expectedValues, expectedFlags);
    }

    void testProgram(const char* prgDesc, const std::vector<uint8_t> &prg, uint8_t expectedCycles,
                     const std::vector<OPAddrInitializer> &initialValues, uint8_t initialFlags,
                     const std::vector<OPAddrInitializer> &expectedValues, uint8_t expectedFlags)
    {
        GIVEN(prgDesc) {
            loadAndReset(prg);
            setFlags(initialFlags);
            for (auto [loadAddr, initialValue] : initialValues) {
                write(loadAddr, initialValue);
            }

            WHEN(std::format("{} cycles are run", expectedCycles)) {
                const size_t usedCycles = cpu->run(expectedCycles);
                THEN(std::format("the program is executed consuming {} cycles", expectedCycles)) {
                    CHECK(usedCycles == expectedCycles);
                    for (auto [loadAddr, expectedValue] : expectedValues) {
                        CHECK((unsigned)read(loadAddr) == (unsigned)expectedValue);
                    }
                    AND_THEN("status flags are properly set") {
                        CHECK((unsigned)cpu->statusFlags() == (unsigned)expectedFlags);
                    }
                }
            }
        }
    }

    std::shared_ptr<nes::MOS6502> cpu;
    std::shared_ptr<nes::Cartridge> cart;
    nes::Bus bus;
};
