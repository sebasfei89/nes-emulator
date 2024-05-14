#include "util.h"

SCENARIO("Load accumulator") {
    NESTest nes;

    // Immediate
    nes.testProgram("LDA #$11", { OP::LDA_IMM, 0x11 }, 2, OPAddr::Acc, 0x00, 0x82, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA #$81", { OP::LDA_IMM, 0x81 }, 2, OPAddr::Acc, 0x00, 0x00, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA #$00", { OP::LDA_IMM, 0x00 }, 2, OPAddr::Acc, 0xFF, 0x00, OPAddr::Acc, 0x00, 0x02);

    // Absolute
    nes.testProgram("LDA $0200 with [$0200] = $11", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA $0200 with [$0200] = $81", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA $0200 with [$0200] = $00", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::Acc, 0x00, 0x02);

    // X-Indexed Absolute
    nes.testProgram("LDA $0200,X with [$0200]=$11 and X=$00", { OP::LDA_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0x00}, {OPAddr::Acc, 0xFF}, {OPAddr::MemABS, 0x00}}, 0x80, OPAddr::Acc, 0x00, 0x02);
    nes.testProgram("LDA $0200,X with [$0201]=$81 and X=$01", { OP::LDA_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0x01}, {OPAddr::MemABS_1, 0x81}}, 0x02, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA $01FF,X with [$0200]=$2A and X=$01", { OP::LDA_XAB, 0xFF, 0x01 }, 5, {{OPAddr::X, 0x01}, {OPAddr::MemABS, 0x2A}}, 0x82, OPAddr::Acc, 0x2A, 0x00);

    // Y-Indexed Absolute
    nes.testProgram("LDA $0200,Y with [$0200]=$00 and Y=0", {OP::LDA_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x00}, {OPAddr::Acc, 0xFF}, {OPAddr::MemABS, 0x00}}, 0x80, OPAddr::Acc, 0x00, 0x02);
    nes.testProgram("LDA $0200,Y with [$0201]=$81 and Y=1", {OP::LDA_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x01}, {OPAddr::MemABS_1, 0x81}}, 0x02, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA $01FF,Y with [$0200]=$2A and Y=1", {OP::LDA_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 0x01}, {OPAddr::MemABS, 0x2A}}, 0x82, OPAddr::Acc, 0x2A, 0x00);
}

SCENARIO("Load X register") {
    NESTest nes;

    // Immediate
    nes.testProgram("LDX #$11", { OP::LDX_IMM, 0x11 }, 2, OPAddr::X, 0x00, 0x82, OPAddr::X, 0x11, 0x00);
    nes.testProgram("LDX #$81", { OP::LDX_IMM, 0x81 }, 2, OPAddr::X, 0x00, 0x00, OPAddr::X, 0x81, 0x80);
    nes.testProgram("LDX #$00", { OP::LDX_IMM, 0x00 }, 2, OPAddr::X, 0xFF, 0x00, OPAddr::X, 0x00, 0x02);

    // Absolute
    nes.testProgram("LDX $0200 with [$0200] = $11", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::X, 0x11, 0x00);
    nes.testProgram("LDX $0200 with [$0200] = $81", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::X, 0x81, 0x80);
    nes.testProgram("LDX $0200 with [$0200] = $00", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::X, 0x00, 0x02);

    // Y-Indexed Absolute
    nes.testProgram("LDX $0200,Y with [$0200]=$00 and Y=0", {OP::LDX_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x00}, {OPAddr::X, 0xFF}, {OPAddr::MemABS, 0x00} }, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("LDX $0200,Y with [$0201]=$81 and Y=1", {OP::LDX_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x01}, {OPAddr::MemABS_1, 0x81} }, 0x02, OPAddr::X, 0x81, 0x80);
    nes.testProgram("LDX $01FF,Y with [$0200]=$2A and Y=1", {OP::LDX_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 0x01}, {OPAddr::MemABS, 0x2A} }, 0x82, OPAddr::X, 0x2A, 0x00);
}

SCENARIO("Load Y register") {
    NESTest nes;

    // Immediate
    nes.testProgram("LDY #$11", { OP::LDY_IMM, 0x11 }, 2, OPAddr::Y, 0x00, 0x82, OPAddr::Y, 0x11, 0x00);
    nes.testProgram("LDY #$81", { OP::LDY_IMM, 0x81 }, 2, OPAddr::Y, 0x00, 0x00, OPAddr::Y, 0x81, 0x80);
    nes.testProgram("LDY #$00", { OP::LDY_IMM, 0x00 }, 2, OPAddr::Y, 0xFF, 0x00, OPAddr::Y, 0x00, 0x02);

    // Absolute
    nes.testProgram("LDY $0200 with [$0200] = $11", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::Y, 0x11, 0x00);
    nes.testProgram("LDY $0200 with [$0200] = $81", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::Y, 0x81, 0x80);
    nes.testProgram("LDY $0200 with [$0200] = $00", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::Y, 0x00, 0x02);

    // X-Indexed Absolute
    nes.testProgram("LDY $0200,X with [$0200]=$11 and Y=$00", { OP::LDY_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0x00}, {OPAddr::Acc, 0xFF}, {OPAddr::MemABS, 0x00}}, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("LDY $0200,X with [$0201]=$81 and Y=$01", { OP::LDY_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0x01}, {OPAddr::MemABS_1, 0x81}}, 0x02, OPAddr::Y, 0x81, 0x80);
    nes.testProgram("LDY $01FF,X with [$0200]=$2A and Y=$01", { OP::LDY_XAB, 0xFF, 0x01 }, 5, {{OPAddr::X, 0x01}, {OPAddr::MemABS, 0x2A}}, 0x82, OPAddr::Y, 0x2A, 0x00);
}

SCENARIO("Store accumulator")
{
    NESTest nes;

    // Immediate
    nes.testProgram("STA $0200 with ACC=$8F", { OP::STA_ABS, 0x00, 0x02 }, 4, OPAddr::Acc, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // X-Indexed Absolute
    nes.testProgram("STA $01FF,X with ACC=$8F and X=$01", { OP::STA_XAB, 0xFF, 0x01 }, 5, {{OPAddr::Acc, 0x8F}, {OPAddr::X, 0x01}}, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // Y-Indexed Absolute
    nes.testProgram("STA $01FF,Y with ACC=$8F and Y=$01", { OP::STA_YAB, 0xFF, 0x01 }, 5, {{OPAddr::Acc, 0x8F}, {OPAddr::Y, 0x01}}, 0x00, OPAddr::MemABS, 0x8F, 0x00);
}

SCENARIO("Store X register")
{
    NESTest nes;

    // Immediate
    nes.testProgram("STX $0200 with ACC = 0x8F", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STX $0200 with ACC = 0x00", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);
}

SCENARIO("Store Y register")
{
    NESTest nes;

    // Immediate
    nes.testProgram("STY $0200 with ACC = 0x8F", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STY $0200 with ACC = 0x00", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);
}
