#include "util.h"

SCENARIO("Arithmetic shift left") {
    NESTest nes;

    // Accumulator
    nes.testProgram("ASL with ACC=0x80", { OP::ASL_ACC }, 2, OPAddr::Acc, 0x80, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ASL with ACC=0x41", { OP::ASL_ACC }, 2, OPAddr::Acc, 0x41, 0x03, OPAddr::Acc, 0x82, 0x80);

    // Absolute
    nes.testProgram("ASL $0200 with [$0200]=0x80", { OP::ASL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ASL $0200 with [$0200]=0x41", { OP::ASL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x41, 0x03, OPAddr::MemABS, 0x82, 0x80);

    // X-Indexed Absolute
    nes.testProgram("ASL $0200,X with [$0200]=$80 and X=0", { OP::ASL_XAB, 0x00, 0x02 }, 7, { {OPAddr::MemABS, 0x80}, {OPAddr::X, 0x00} }, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ASL $01FF,X with [$0200]=$41 and X=1", { OP::ASL_XAB, 0xFF, 0x01 }, 7, { {OPAddr::MemABS, 0x41}, {OPAddr::X, 0x01} }, 0x03, OPAddr::MemABS, 0x82, 0x80);

    // Zero Page
    nes.testProgram("ASL $00 with [$0000]=0x80", { OP::ASL_ZPG, 0x00 }, 5, OPAddr::MemZeroPage, 0x80, 0x80, OPAddr::MemZeroPage, 0x00, 0x03);
    nes.testProgram("ASL $01 with [$0001]=0x41", { OP::ASL_ZPG, 0x01 }, 5, OPAddr::MemZeroPage_1, 0x41, 0x03, OPAddr::MemZeroPage_1, 0x82, 0x80);
}

SCENARIO("Logical shift right") {
    NESTest nes;

    // Accumulator
    nes.testProgram("LSR with ACC=0x01", { OP::LSR_ACC }, 2, OPAddr::Acc, 0x01, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("LSR with ACC=0x80", { OP::LSR_ACC }, 2, OPAddr::Acc, 0x80, 0x83, OPAddr::Acc, 0x40, 0x00);

    // Absolute
    nes.testProgram("LSR $0200 with [$0200]=0x01", { OP::LSR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("LSR $0200 with [$0200]=0x80", { OP::LSR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x83, OPAddr::MemABS, 0x40, 0x00);

    // X-Indexed Absolute
    nes.testProgram("LSR $0200,X with [$0200]=$01 and X=0", { OP::LSR_XAB, 0x00, 0x02 }, 7, {{OPAddr::MemABS, 0x01}, {OPAddr::X, 0x00}}, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("LSR $01FF,X with [$0200]=$80 and X=1", { OP::LSR_XAB, 0xFF, 0x01 }, 7, {{OPAddr::MemABS, 0x80}, {OPAddr::X, 0x01}}, 0x83, OPAddr::MemABS, 0x40, 0x00);

    // Zero Page
    nes.testProgram("LSR $00 with [$0000]=0x01", {OP::LSR_ZPG, 0x00}, 5, OPAddr::MemZeroPage, 0x01, 0x80, OPAddr::MemZeroPage, 0x00, 0x03);
    nes.testProgram("LSR $01 with [$0001]=0x80", {OP::LSR_ZPG, 0x01}, 5, OPAddr::MemZeroPage_1, 0x80, 0x83, OPAddr::MemZeroPage_1, 0x40, 0x00);
}

SCENARIO("Rotate left") {
    NESTest nes;

    // Accumulator
    nes.testProgram("ROL with ACC=0x80 and C=0", { OP::ROL_ACC }, 2, OPAddr::Acc, 0x80, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ROL with ACC=0x40 and C=1", { OP::ROL_ACC }, 2, OPAddr::Acc, 0x40, 0x03, OPAddr::Acc, 0x81, 0x80);

    // Absolute
    nes.testProgram("ROL $2000 with [$2000]=0x80 and C=0", { OP::ROL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROL $2000 with [$2000]=0x40 and C=1", { OP::ROL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x40, 0x03, OPAddr::MemABS, 0x81, 0x80);

    // X-Indexed Absolute
    nes.testProgram("ROL $0200,X with [$0200]=0x80 and X=0 and C=0", { OP::ROL_XAB, 0x00, 0x02 }, 7, {{OPAddr::MemABS, 0x80}, {OPAddr::X, 0}}, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROL $01FF,X with [$0200]=0x40 and X=1 and C=1", { OP::ROL_XAB, 0xFF, 0x01 }, 7, {{OPAddr::MemABS, 0x40}, {OPAddr::X, 1}}, 0x03, OPAddr::MemABS, 0x81, 0x80);

    // Zero Page
    nes.testProgram("ROL $00 with [$0000]=0x80 and C=0", {OP::ROL_ZPG, 0x00}, 5, OPAddr::MemZeroPage, 0x80, 0x80, OPAddr::MemZeroPage, 0x00, 0x03);
    nes.testProgram("ROL $01 with [$0001]=0x40 and C=1", {OP::ROL_ZPG, 0x01}, 5, OPAddr::MemZeroPage_1, 0x40, 0x03, OPAddr::MemZeroPage_1, 0x81, 0x80);
}

SCENARIO("Rotate right") {
    NESTest nes;

    // Accumulator
    nes.testProgram("ROR with ACC=0x01 and C=0", { OP::ROR_ACC }, 2, OPAddr::Acc, 0x01, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ROR with ACC=0x02 and C=1", { OP::ROR_ACC }, 2, OPAddr::Acc, 0x02, 0x03, OPAddr::Acc, 0x81, 0x80);

    // Absolute
    nes.testProgram("ROR $2000 with [$2000]=0x01 and C=0", { OP::ROR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROR $2000 with [$2000]=0x02 and C=1", { OP::ROR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x02, 0x03, OPAddr::MemABS, 0x81, 0x80);

    // X-Indexed Absolute
    nes.testProgram("ROR $0200,X with [$0200]=0x01 and X=0 and C=0", { OP::ROR_XAB, 0x00, 0x02 }, 7, {{OPAddr::MemABS, 0x01}, {OPAddr::X, 0}}, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROR $01FF,X with [$0200]=0x02 and X=1 and C=1", { OP::ROR_XAB, 0xFF, 0x01 }, 7, {{OPAddr::MemABS, 0x02}, {OPAddr::X, 1}}, 0x03, OPAddr::MemABS, 0x81, 0x80);

    // Zero Page
    nes.testProgram("ROR $00 with [$0000]=0x01 and C=0", {OP::ROR_ZPG, 0x00}, 5, OPAddr::MemZeroPage, 0x01, 0x80, OPAddr::MemZeroPage, 0x00, 0x03);
    nes.testProgram("ROR $01 with [$0001]=0x02 and C=1", {OP::ROR_ZPG, 0x01}, 5, OPAddr::MemZeroPage_1, 0x02, 0x03, OPAddr::MemZeroPage_1, 0x81, 0x80);
}
