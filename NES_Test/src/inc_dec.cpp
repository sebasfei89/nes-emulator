#include "util.h"

SCENARIO("Decrement instructions")
{
    NESTest nes;

    // Implied
    nes.testProgram("DEX with X = $01", { OP::DEX_IMP }, 2, OPAddr::X, 0x01, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("DEX with X = $00", { OP::DEX_IMP }, 2, OPAddr::X, 0x00, 0x02, OPAddr::X, 0xFF, 0x80);
    nes.testProgram("DEY with Y = $01", { OP::DEY_IMP }, 2, OPAddr::Y, 0x01, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("DEY with Y = $00", { OP::DEY_IMP }, 2, OPAddr::Y, 0x00, 0x02, OPAddr::Y, 0xFF, 0x80);

    // Absolute
    nes.testProgram("DEC $0200 with [$0200] = $01", { OP::DEC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("DEC $0200 with [$0200] = $00", { OP::DEC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x00, 0x02, OPAddr::MemABS, 0xFF, 0x80);

    // X-Indexed Absolute
    nes.testProgram("DEC $0200,X with X=0 and [$0200]=1", {OP::DEC_XAB, 0x00, 0x02}, 7, {{OPAddr::MemABS, 1}, {OPAddr::X, 0}}, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("DEC $01FF,X with X=1 and [$0200]=0", {OP::DEC_XAB, 0xFF, 0x01}, 7, {{OPAddr::MemABS, 0}, {OPAddr::X, 1}}, 0x02, OPAddr::MemABS, 0xFF, 0x80);

    // Zero Page
    nes.testProgram("DEC $00 with [$0000]=1", {OP::DEC_ZPG, 0}, 5, OPAddr::MemZeroPage, 1, 0x80, OPAddr::MemZeroPage, 0x00, 0x02);
    nes.testProgram("DEC $01 with [$0001]=0", {OP::DEC_ZPG, 1}, 5, OPAddr::MemZeroPage_1, 0, 0x02, OPAddr::MemZeroPage_1, 0xFF, 0x80);

    // X-Indexed Zero Page
    nes.testProgram("DEC $00,X with X=1 and [$0001]=1", {OP::DEC_XZP, 0x00}, 6, {{OPAddr::MemZeroPage_1, 1}, {OPAddr::X, 1}}, 0x80, OPAddr::MemZeroPage_1, 0x00, 0x02);
    nes.testProgram("DEC $FF,X with X=1 and [$0000]=0", {OP::DEC_XZP, 0xFF}, 6, {{OPAddr::MemZeroPage, 0}, {OPAddr::X, 1}}, 0x02, OPAddr::MemZeroPage, 0xFF, 0x80);
}

SCENARIO("Increment instructions")
{
    NESTest nes;

    // Implied
    nes.testProgram("INX with X = $FF", { OP::INX_IMP }, 2, OPAddr::X, 0xFF, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("INX with X = $7F", { OP::INX_IMP }, 2, OPAddr::X, 0x7F, 0x02, OPAddr::X, 0x80, 0x80);
    nes.testProgram("INY with Y = $FF", { OP::INY_IMP }, 2, OPAddr::Y, 0xFF, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("INY with Y = $7F", { OP::INY_IMP }, 2, OPAddr::Y, 0x7F, 0x02, OPAddr::Y, 0x80, 0x80);

    // Absolute
    nes.testProgram("INC $0200 with [$0200] = $FF", { OP::INC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0xFF, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("INC $0200 with [$0200] = $7F", { OP::INC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x7F, 0x02, OPAddr::MemABS, 0x80, 0x80);

    // X-Indexed Absolute
    nes.testProgram("INC $0200,X with X=0 and [$0200]=$FF", {OP::INC_XAB, 0x00, 0x02}, 7, {{OPAddr::MemABS, 0xFF}, {OPAddr::X, 0}}, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("INC $01FF,X with X=1 and [$0200]=$7F", {OP::INC_XAB, 0xFF, 0x01}, 7, {{OPAddr::MemABS, 0x7F}, {OPAddr::X, 1}}, 0x02, OPAddr::MemABS, 0x80, 0x80);

    // Zero Page
    nes.testProgram("INC $00 with [$0000]=$FF", {OP::INC_ZPG, 0}, 5, OPAddr::MemZeroPage, 0xFF, 0x80, OPAddr::MemZeroPage, 0x00, 0x02);
    nes.testProgram("INC $01 with [$0001]=$7F", {OP::INC_ZPG, 1}, 5, OPAddr::MemZeroPage_1, 0x7F, 0x02, OPAddr::MemZeroPage_1, 0x80, 0x80);

    // X-Indexed Zero Page
    nes.testProgram("INC $00,X with X=1 and [$0001]=$FF", {OP::INC_XZP, 0x00}, 6, {{OPAddr::MemZeroPage_1, 0xFF}, {OPAddr::X, 1}}, 0x80, OPAddr::MemZeroPage_1, 0x00, 0x02);
    nes.testProgram("INC $FF,X with X=1 and [$0000]=$7F", {OP::INC_XZP, 0xFF}, 6, {{OPAddr::MemZeroPage, 0x7F}, {OPAddr::X, 1}}, 0x02, OPAddr::MemZeroPage, 0x80, 0x80);
}
