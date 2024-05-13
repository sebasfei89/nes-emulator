#include "util.h"

SCENARIO("TAX instruction")
{
    NESTest nes;

    // TAX
    nes.testProgram("TAX with ACC = $13", { OP::TAX_IMP }, 2, OPAddr::Acc, 0x13, 0x82, {{OPAddr::Acc, 0x13}, {OPAddr::X, 0x13}}, 0x00);
    nes.testProgram("TAX with ACC = $83", { OP::TAX_IMP }, 2, OPAddr::Acc, 0x83, 0x02, {{OPAddr::Acc, 0x83}, {OPAddr::X, 0x83}}, 0x80);
    nes.testProgram("TAX with ACC = $00", { OP::TAX_IMP }, 2, {{OPAddr::Acc, 0x00}, {OPAddr::X, 0x24}}, 0x80, {{OPAddr::Acc, 0x00}, {OPAddr::X, 0x00}}, 0x02);

    // TAY
    nes.testProgram("TAY with ACC = $13", { OP::TAY_IMP }, 2, OPAddr::Acc, 0x13, 0x82, { {OPAddr::Acc, 0x13}, {OPAddr::Y, 0x13} }, 0x00);
    nes.testProgram("TAY with ACC = $83", { OP::TAY_IMP }, 2, OPAddr::Acc, 0x83, 0x02, { {OPAddr::Acc, 0x83}, {OPAddr::Y, 0x83} }, 0x80);
    nes.testProgram("TAY with ACC = $00", { OP::TAY_IMP }, 2, {{OPAddr::Acc, 0x00}, {OPAddr::Y, 0x24} }, 0x80, { {OPAddr::Acc, 0x00}, {OPAddr::Y, 0x00} }, 0x02);

    // TSX
    nes.testProgram("TSX with SP = $FF", { OP::TSX_IMP }, 2, {}, 0x02, OPAddr::X, 0xFF, 0x80);
    nes.testProgram("TSX with SP = $08", { OP::TSX_IMP }, 2, OPAddr::SP, 0x08, 0x82, OPAddr::X, 0x08, 0x00);
    nes.testProgram("TSX with SP = $00", { OP::TSX_IMP }, 2, {{OPAddr::SP, 0x00}, {OPAddr::X, 0x24}}, 0x80, OPAddr::X, 0x00, 0x02);

    // TXA
    nes.testProgram("TXA with X = $13", { OP::TXA_IMP }, 2, OPAddr::X, 0x13, 0x82, OPAddr::Acc, 0x13, 0x00);
    nes.testProgram("TXA with X = $83", { OP::TXA_IMP }, 2, OPAddr::X, 0x83, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("TXA with X = $00", { OP::TXA_IMP }, 2, {{OPAddr::X, 0x00}, {OPAddr::Acc, 0x24}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // TYA
    nes.testProgram("TYA with Y = $13", { OP::TYA_IMP }, 2, OPAddr::Y, 0x13, 0x82, OPAddr::Acc, 0x13, 0x00);
    nes.testProgram("TYA with Y = $83", { OP::TYA_IMP }, 2, OPAddr::Y, 0x83, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("TYA with Y = $00", { OP::TYA_IMP }, 2, {{OPAddr::Y, 0x00}, {OPAddr::Acc, 0x24}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // TXS
    nes.testProgram("TXS with X = $13", { OP::TXS_IMP }, 2, OPAddr::X, 0x13, 0x82, OPAddr::SP, 0x13, 0x00);
    nes.testProgram("TXS with X = $83", { OP::TXS_IMP }, 2, OPAddr::X, 0x83, 0x02, OPAddr::SP, 0x83, 0x80);
    nes.testProgram("TXS with X = $00", { OP::TXS_IMP }, 2, OPAddr::X, 0x00, 0x80, OPAddr::SP, 0x00, 0x02);
}
