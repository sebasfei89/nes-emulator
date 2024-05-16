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

    // Zero Page
    nes.testProgram("LDA $00 with [$0000]=$00", {OP::LDA_ZPG, 0x00}, 3, {{OPAddr::MemZeroPage, 0x00}, {OPAddr::Acc, 0xFF}}, 0x80, OPAddr::Acc, 0x00, 0x02);
    nes.testProgram("LDA $01 with [$0001]=$81", {OP::LDA_ZPG, 0x01}, 3, {{OPAddr::MemZeroPage_1, 0x81}, {OPAddr::Acc, 0xFF}}, 0x02, OPAddr::Acc, 0x81, 0x80);

    // X-Indexed Zero Page
    nes.testProgram("LDA $00,X with [$0001]=$11 and X=$01", {OP::LDA_XZP, 0x00}, 4, {{OPAddr::MemZeroPage_1, 0x11}, {OPAddr::Acc, 0xFF}, {OPAddr::X, 1}}, 0x80, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA $01,X with [$0000]=$81 and X=$FF", {OP::LDA_XZP, 0x01}, 4, {{OPAddr::MemZeroPage, 0x81}, {OPAddr::Acc, 0xFF}, {OPAddr::X, 0xFF}}, 0x02, OPAddr::Acc, 0x81, 0x80);

    // X-Indexed Zero Page Indirect
    nes.testProgram("LDA ($00,X) with X=0 and [$0000]=$00 [$0001]=$02 [$0200]=$11", {OP::LDA_XZI, 0x00}, 6, {{OPAddr::X, 0}, {OPAddr::MemZeroPage, 0}, {OPAddr::MemZeroPage_1, 0x02}, {OPAddr::MemABS, 0x11}}, 0x80, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA ($FF,X) with X=1 and [$0000]=$01 [$0001]=$02 [$0201]=$81", {OP::LDA_XZI, 0xFF}, 6, {{OPAddr::X, 1}, {OPAddr::MemZeroPage, 1}, {OPAddr::MemZeroPage_1, 0x02}, {OPAddr::MemABS_1, 0x81}}, 0x02, OPAddr::Acc, 0x81, 0x80);

    // Zero Page Indirect Y-Indexed
    nes.testProgram("LDA ($00),Y with Y=1 and [$0000]=$00 [$0001]=$02 [$0201]=$11", {OP::LDA_ZIY, 0x00}, 5, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS_1, 0x11} }, 0x80, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA ($00),Y with Y=1 and [$0000]=$FF [$0001]=$01 [$0200]=$81", {OP::LDA_ZIY, 0x00}, 6, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage, 0xFF}, {OPAddr::MemZeroPage_1, 1}, {OPAddr::MemABS, 0x81} }, 0x02, OPAddr::Acc, 0x81, 0x80);
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

    // Zero Page
    nes.testProgram("LDX $00 with [$0000]=$11", {OP::LDX_ZPG, 0x00}, 3, {{OPAddr::MemZeroPage, 0x00}, {OPAddr::X, 0xFF}}, 0x80, OPAddr::X, 0x00, 0x02);
    nes.testProgram("LDX $01 with [$0001]=$81", {OP::LDX_ZPG, 0x01}, 3, {{OPAddr::MemZeroPage_1, 0x81}, {OPAddr::X, 0xFF}}, 0x02, OPAddr::X, 0x81, 0x80);

    // Y-Indexed Zero Page
    nes.testProgram("LDX $00,Y with [$0001]=$11 and Y=$01", {OP::LDX_YZP, 0 }, 4, {{OPAddr::MemZeroPage_1, 0x11}, {OPAddr::X, 0xFF}, {OPAddr::Y, 1}}, 0x80, OPAddr::X, 0x11, 0x00);
    nes.testProgram("LDX $01,Y with [$0000]=$81 and Y=$FF", {OP::LDX_YZP, 1 }, 4, {{OPAddr::MemZeroPage, 0x81}, {OPAddr::X, 0xFF}, {OPAddr::Y, 0xFF}}, 0x02, OPAddr::X, 0x81, 0x80);
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

    // Zero Page
    nes.testProgram("LDY $00 with [$0000]=$11", {OP::LDY_ZPG, 0x00}, 3, {{OPAddr::MemZeroPage, 0x00}, {OPAddr::Y, 0xFF}}, 0x80, OPAddr::Y, 0x00, 0x02);
    nes.testProgram("LDY $01 with [$0001]=$81", {OP::LDY_ZPG, 0x01}, 3, {{OPAddr::MemZeroPage_1, 0x81}, {OPAddr::Y, 0xFF}}, 0x02, OPAddr::Y, 0x81, 0x80);

    // X-Indexed Zero Page
    nes.testProgram("LDY $00,X with [$0001]=$11 and X=$01", {OP::LDY_XZP, 0}, 4, {{OPAddr::MemZeroPage_1, 0x11}, {OPAddr::Y, 0xFF}, {OPAddr::X, 1}}, 0x80, OPAddr::Y, 0x11, 0x00);
    nes.testProgram("LDY $01,X with [$0000]=$81 and X=$FF", {OP::LDY_XZP, 1}, 4, {{OPAddr::MemZeroPage, 0x81}, {OPAddr::Y, 0xFF}, {OPAddr::X, 0xFF}}, 0x02, OPAddr::Y, 0x81, 0x80);
}

SCENARIO("Store accumulator")
{
    NESTest nes;

    // Absolute
    nes.testProgram("STA $0200 with ACC=$8F", { OP::STA_ABS, 0x00, 0x02 }, 4, OPAddr::Acc, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // X-Indexed Absolute
    nes.testProgram("STA $01FF,X with ACC=$8F and X=$01", { OP::STA_XAB, 0xFF, 0x01 }, 5, {{OPAddr::Acc, 0x8F}, {OPAddr::X, 0x01}}, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // Y-Indexed Absolute
    nes.testProgram("STA $01FF,Y with ACC=$8F and Y=$01", { OP::STA_YAB, 0xFF, 0x01 }, 5, {{OPAddr::Acc, 0x8F}, {OPAddr::Y, 0x01}}, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // Zero Page
    nes.testProgram("STA $01 with ACC=$8F", {OP::STA_ZPG, 0x01}, 3, OPAddr::Acc, 0x8F, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);

    // X-Indexed Zero Page
    nes.testProgram("STA $00,X with ACC=$8F and X=1", {OP::STA_XZP, 0x00}, 4, {{OPAddr::Acc, 0x8F}, {OPAddr::X, 1}}, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);

    // X-Indexed Zero Page Indirect
    nes.testProgram("STA ($FF,X) with ACC=$8F and X=1 and [$0000]=$00 [$0001]=$02", {OP::STA_XZI, 0xFF}, 6, {{OPAddr::Acc, 0x8F}, {OPAddr::X, 1}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 0x02}}, 0x00, OPAddr::MemABS, 0x8F, 0x00);

    // Zero Page Indirect Y-Indexed
    nes.testProgram("STA ($00),Y with Y=1 and [$0000]=$00 [$0001]=$02 and ACC=$11", {OP::STA_ZIY, 0x00}, 6, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::Acc, 0x11}}, 0x80, OPAddr::MemABS_1, 0x11, 0x80);
    nes.testProgram("STA ($00),Y with Y=1 and [$0000]=$FF [$0001]=$01 and ACC=$81", {OP::STA_ZIY, 0x00}, 6, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage, 0xFF}, {OPAddr::MemZeroPage_1, 1}, {OPAddr::Acc, 0x81}}, 0x02, OPAddr::MemABS, 0x81, 0x02);
}

SCENARIO("Store X register")
{
    NESTest nes;

    // Absolute
    nes.testProgram("STX $0200 with X=$8F", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STX $0200 with X=$00", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);

    // Zero Page
    nes.testProgram("STX $01 with X=$8F", {OP::STX_ZPG, 0x01}, 3, OPAddr::X, 0x8F, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);

    // Y-Indexed Zero Page
    nes.testProgram("STX $00,Y with X=$8F and Y=1", {OP::STX_YZP, 0x00 }, 4, {{OPAddr::Y, 1}, {OPAddr::X, 0x8F}}, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);
}

SCENARIO("Store Y register")
{
    NESTest nes;

    // Absolute
    nes.testProgram("STY $0200 with ACC=$8F", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STY $0200 with ACC=$00", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);

    // Zero Page
    nes.testProgram("STY $01 with Y=$8F", {OP::STY_ZPG, 0x01}, 3, OPAddr::Y, 0x8F, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);

    // X-Indexed Zero Page
    nes.testProgram("STY $00,X with and X=1 and Y=$8F", {OP::STY_XZP, 0x00}, 4, {{OPAddr::Y, 0x8F}, {OPAddr::X, 1}}, 0x00, OPAddr::MemZeroPage_1, 0x8F, 0x00);
}
