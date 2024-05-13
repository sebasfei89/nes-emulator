#include "util.h"

SCENARIO("Control flow instruction")
{
    NESTest nes;
    nes.testProgram("BRK", { OP::BRK_IMP }, 7,
        {{OPAddr::MemIRQ_HI, 0x40}, {OPAddr::MemIRQ_LO, 0x20}}, 0x41, // Initial state
        {{OPAddr::MemSTK_0, 0x01}, {OPAddr::MemSTK_1, 0x80}, {OPAddr::MemSTK_2, 0x41}, {OPAddr::SP, 0xFC}, {OPAddr::PC_HI, 0x40}, {OPAddr::PC_LO, 0x20}}, 0x51); // Expected state

    nes.testProgram("RTI", { OP::RTI_IMP }, 6,
        {{OPAddr::MemSTK_0, 0x20}, {OPAddr::MemSTK_1, 0x40}, {OPAddr::MemSTK_2, 0x41}, {OPAddr::SP, 0xFC}}, 0x00, // Initial state
        {{OPAddr::PC_HI, 0x40}, {OPAddr::PC_LO, 0x20}, {OPAddr::SP, 0xFF} }, 0x41); // Expected state

    nes.testProgram("RTS", { OP::RTS_IMP }, 6,
        { {OPAddr::MemSTK_0, 0x20}, {OPAddr::MemSTK_1, 0x40}, {OPAddr::SP, 0xFD} }, 0x00, // Initial state
        { {OPAddr::PC_HI, 0x40}, {OPAddr::PC_LO, 0x21}, {OPAddr::SP, 0xFF} }, 0x00); // Expected state

    nes.testProgram("JMP $4020", { OP::JMP_ABS, 0x20, 0x40 }, 3, {}, 0x00, {{OPAddr::PC_HI, 0x40}, {OPAddr::PC_LO, 0x20}}, 0x00);
    nes.testProgram("JMP ($0200)", { OP::JMP_IND, 0x00, 0x02 }, 5, {{OPAddr::MemABS, 0x30},{OPAddr::MemABS_1, 0x50}}, 0x00, {{OPAddr::PC_HI, 0x50}, {OPAddr::PC_LO, 0x30}}, 0x00);
    nes.testProgram("JMP ($02FF)", { OP::JMP_IND, 0xFF, 0x02 }, 5, {{OPAddr::MemABS_IND, 0x30},{OPAddr::MemABS, 0x50}}, 0x00, {{OPAddr::PC_HI, 0x50}, {OPAddr::PC_LO, 0x30}}, 0x00);

    nes.testProgram("JSR $4020", { OP::JSR_ABS, 0x20, 0x40 }, 6, {}, 0x00, {{OPAddr::PC_HI, 0x40}, {OPAddr::PC_LO, 0x20}, {OPAddr::SP, 0xFD}, {OPAddr::MemSTK_0, 0x80}, {OPAddr::MemSTK_1, 0x02}}, 0x00);
}
