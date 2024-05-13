#include "util.h"

SCENARIO("Decrement instructions")
{
    NESTest nes;

    nes.testProgram("DEX with X = $01", { OP::DEX_IMP }, 2, OPAddr::X, 0x01, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("DEX with X = $00", { OP::DEX_IMP }, 2, OPAddr::X, 0x00, 0x02, OPAddr::X, 0xFF, 0x80);
    
    nes.testProgram("DEY with Y = $01", { OP::DEY_IMP }, 2, OPAddr::Y, 0x01, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("DEY with Y = $00", { OP::DEY_IMP }, 2, OPAddr::Y, 0x00, 0x02, OPAddr::Y, 0xFF, 0x80);

    nes.testProgram("DEC $0200 with [$0200] = $01", { OP::DEC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("DEC $0200 with [$0200] = $00", { OP::DEC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x00, 0x02, OPAddr::MemABS, 0xFF, 0x80);
}

SCENARIO("Increment instructions")
{
    NESTest nes;

    nes.testProgram("INX with X = $FF", { OP::INX_IMP }, 2, OPAddr::X, 0xFF, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("INX with X = $7F", { OP::INX_IMP }, 2, OPAddr::X, 0x7F, 0x02, OPAddr::X, 0x80, 0x80);

    nes.testProgram("INY with Y = $FF", { OP::INY_IMP }, 2, OPAddr::Y, 0xFF, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("INY with Y = $7F", { OP::INY_IMP }, 2, OPAddr::Y, 0x7F, 0x02, OPAddr::Y, 0x80, 0x80);

    nes.testProgram("INC $0200 with [$0200] = $FF", { OP::INC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0xFF, 0x80, OPAddr::MemABS, 0x00, 0x02);
    nes.testProgram("INC $0200 with [$0200] = $7F", { OP::INC_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x7F, 0x02, OPAddr::MemABS, 0x80, 0x80);
}
