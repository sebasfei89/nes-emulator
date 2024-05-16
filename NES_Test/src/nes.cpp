#include "./util.h"

// Addressing modes tested:
// DONE:
//  Implied
//  Accumulator
//  Immediate
//  Absolute
//  Absolute Indirect
//  X-Indexed Absolute
//  Y-Indexed Absolute
//  Zero Page
//  X-Indexed Zero Page
// TODO:
//  Y-Indexed Zero Page
//  X-Indexed Zero Page Indirect
//  Zero Page Indirect Y-Indexed
//  Relative

SCENARIO("NES MOS6502 cpu initialization")
{
    GIVEN("A MOS6502 cpu with some random state")
    {
        NESTest nes;
        WHEN("When the cpu is reset")
        {
            nes.cpu->reset();

            THEN( "Registers & status are properly reset" )
            {
                REQUIRE(nes.cpu->statusFlags() == 0x00);
                REQUIRE(nes.cpu->programCounter() == NESTest::PROGRAM_STARTUP_ADDR);
                REQUIRE(nes.cpu->stackPointer() == 0xFF);
                REQUIRE(nes.cpu->accumulator() == 0x00);
                REQUIRE(nes.cpu->xRegister() == 0x00);
                REQUIRE(nes.cpu->yRegister() == 0x00);
                for (uint16_t i = 0; i < 0x0800; ++i)
                {
                    REQUIRE(nes.cpu->ram().mData[i] == 0x00);
                }
            }
        }
    }
}

SCENARIO("NOP instruction")
{
    NESTest nes;
    nes.testProgram("NOP", {OP::NOP_IMP}, 2, OPAddr::Acc, 0x00, 0x41, OPAddr::Acc, 0x00, 0x41);
}

SCENARIO("Undocumented instruction")
{
    NESTest nes;
    nes.testProgram("UNDOCUMENTED_OP", {0xFF}, 2, {}, 0x41, {}, 0x41);
}
