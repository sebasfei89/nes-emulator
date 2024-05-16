#include "util.h"

SCENARIO("Add to accumulator with carry")
{
    NESTest nes;
    
    // Immediate
    nes.testProgram("ADC #$01 with ACC = $02 and C = 0", { OP::ADC_IMM, 0x01 }, 2, OPAddr::Acc, 0x02, 0xC2, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("ADC #$01 with ACC = $02 and C = 1", { OP::ADC_IMM, 0x01 }, 2, OPAddr::Acc, 0x02, 0xC3, OPAddr::Acc, 0x04, 0x00);
    nes.testProgram("ADC #$01 with ACC = $FF and C = 0", { OP::ADC_IMM, 0x01 }, 2, OPAddr::Acc, 0xFF, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC #$01 with ACC = $7F and C = 0", { OP::ADC_IMM, 0x01 }, 2, OPAddr::Acc, 0x7F, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // Absolute
    nes.testProgram("ADC $0200 with [$0200] = $01 and ACC = $02 and C = 0", { OP::ADC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x02},{OPAddr::MemABS, 0x01}}, 0xC2, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("ADC $0200 with [$0200] = $01 and ACC = $02 and C = 1", { OP::ADC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x02},{OPAddr::MemABS, 0x01}}, 0xC3, OPAddr::Acc, 0x04, 0x00);
    nes.testProgram("ADC $0200 with [$0200] = $01 and ACC = $FF and C = 0", { OP::ADC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xFF},{OPAddr::MemABS, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC $0200 with [$0200] = $01 and ACC = $7F and C = 0", { OP::ADC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x7F},{OPAddr::MemABS, 0x01}}, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // X-Indexed Absolute
    nes.testProgram("ADC $0200,X with X=0 and [$0200]=1 and ACC=$02 and C=0", {OP::ADC_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 0}, {OPAddr::Acc, 0x02},{OPAddr::MemABS, 0x01} }, 0xC2, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("ADC $0200,X with X=1 and [$0201]=1 and ACC=$02 and C=1", {OP::ADC_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x02},{OPAddr::MemABS_1, 0x01} }, 0xC3, OPAddr::Acc, 0x04, 0x00);
    nes.testProgram("ADC $01FF,X with X=1 and [$0200]=1 and ACC=$FF and C=0", {OP::ADC_XAB, 0xFF, 0x01}, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0xFF},{OPAddr::MemABS, 0x01} }, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC $01FF,X with X=1 and [$0200]=1 and ACC=$7F and C=0", {OP::ADC_XAB, 0xFF, 0x01}, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0x7F},{OPAddr::MemABS, 0x01} }, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // Y-Indexed Absolute
    nes.testProgram("ADC $0200,Y with Y=0 and [$0200]=1 and ACC=$02 and C=0", {OP::ADC_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0}, {OPAddr::Acc, 0x02},{OPAddr::MemABS, 0x01}}, 0xC2, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("ADC $0200,Y with Y=1 and [$0201]=1 and ACC=$02 and C=1", {OP::ADC_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x02},{OPAddr::MemABS_1, 0x01}}, 0xC3, OPAddr::Acc, 0x04, 0x00);
    nes.testProgram("ADC $01FF,Y with Y=1 and [$0200]=1 and ACC=$FF and C=0", {OP::ADC_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0xFF},{OPAddr::MemABS, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC $01FF,Y with Y=1 and [$0200]=1 and ACC=$7F and C=0", {OP::ADC_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F},{OPAddr::MemABS, 0x01}}, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // Zero Page
    nes.testProgram("ADC $00 with [$0000]=1 and ACC=$FE and C=1", {OP::ADC_ZPG, 0x00}, 3, {{OPAddr::Acc, 0xFE}, {OPAddr::MemZeroPage, 0x01}}, 0xC1, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC $01 with [$0001]=1 and ACC=$7F and C=0", {OP::ADC_ZPG, 0x01}, 3, {{OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage_1, 0x01}}, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // X-Indexed Zero Page
    nes.testProgram("ADC $00,X with X=1 and [$0001]=1 and ACC=$FE and C=1", {OP::ADC_XZP, 0x00}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0xFE}, {OPAddr::MemZeroPage_1, 1}}, 0xC1, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ADC $FF,X with X=1 and [$0000]=1 and ACC=$7F and C=0", {OP::ADC_XZP, 0xFF}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 1}}, 0x02, OPAddr::Acc, 0x80, 0xC0);

    // X-Indexed Zero Page Indirect
    nes.testProgram("ADC ($FF,X) with X=1 and ACC=$7F and C=0 and [$0000]=$00 [$0001]=$02 [$0200]=1", {OP::ADC_XZI, 0xFF}, 6, {{OPAddr::Acc, 0x7F}, {OPAddr::X, 1}, {OPAddr::MemZeroPage, 0}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS, 1}}, 0x00, OPAddr::Acc, 0x80, 0xC0);

    // Zero Page Indirect Y-Indexed
    nes.testProgram("ADC ($00),Y with Y=1 and ACC=$7F and C=0 and [$0000]=$00 [$0001]=$02 [$0201]=1", {OP::ADC_ZIY, 0x00}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS_1, 1} }, 0x00, OPAddr::Acc, 0x80, 0xC0);
    nes.testProgram("ADC ($00),Y with Y=1 and ACC=$7F and C=0 and [$0000]=$FF [$0001]=$01 [$0200]=1", {OP::ADC_ZIY, 0x00}, 6, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 0xFF}, {OPAddr::MemZeroPage_1, 1}, {OPAddr::MemABS, 1}}, 0x00, OPAddr::Acc, 0x80, 0xC0);
}

SCENARIO("Compare with accumulator")
{
    NESTest nes;

    // Immediate
    nes.testProgram("CMP #$01 with ACC=1", { OP::CMP_IMM, 0x01 }, 2, OPAddr::Acc, 0x01, 0x80, OPAddr::Acc, 0x01, 0x03);
    nes.testProgram("CMP #$01 with ACC=2", { OP::CMP_IMM, 0x01 }, 2, OPAddr::Acc, 0x02, 0x82, OPAddr::Acc, 0x02, 0x01);
    nes.testProgram("CMP #$02 with ACC=1", { OP::CMP_IMM, 0x02 }, 2, OPAddr::Acc, 0x01, 0x03, OPAddr::Acc, 0x01, 0x80);

    // Absolute
    nes.testProgram("CMP $0200 with [$0200]=1 and ACC=1", {OP::CMP_ABS, 0x00, 0x02}, 4, {{OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x01}}, 0x80, OPAddr::Acc, 0x01, 0x03);
    nes.testProgram("CMP $0200 with [$0200]=1 and ACC=2", {OP::CMP_ABS, 0x00, 0x02}, 4, {{OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x01}}, 0x82, OPAddr::Acc, 0x02, 0x01);
    nes.testProgram("CMP $0200 with [$0200]=2 and ACC=1", {OP::CMP_ABS, 0x00, 0x02}, 4, {{OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x02}}, 0x03, OPAddr::Acc, 0x01, 0x80);

    // X-Indexed Absolute
    nes.testProgram("CMP $0200,X with X=0 and [$0200]=1 and ACC=1", {OP::CMP_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 0x00}, {OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x01}}, 0x80, OPAddr::Acc, 0x01, 0x03);
    nes.testProgram("CMP $0200,X with X=1 and [$0201]=1 and ACC=2", {OP::CMP_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 0x01}, {OPAddr::Acc, 0x02}, {OPAddr::MemABS_1, 0x01}}, 0x82, OPAddr::Acc, 0x02, 0x01);
    nes.testProgram("CMP $01FF,X with X=1 and [$0200]=2 and ACC=1", {OP::CMP_XAB, 0xFF, 0x01}, 5, {{OPAddr::X, 0x01}, {OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x02}}, 0x03, OPAddr::Acc, 0x01, 0x80);

    // Y-Indexed Absolute
    nes.testProgram("CMP $0200,Y with Y=0 and [$0200]=1 and ACC=1", {OP::CMP_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x00}, {OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x01}}, 0x80, OPAddr::Acc, 0x01, 0x03);
    nes.testProgram("CMP $0200,Y with Y=1 and [$0201]=1 and ACC=2", {OP::CMP_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0x01}, {OPAddr::Acc, 0x02}, {OPAddr::MemABS_1, 0x01}}, 0x82, OPAddr::Acc, 0x02, 0x01);
    nes.testProgram("CMP $01FF,Y with Y=1 and [$0200]=2 and ACC=1", {OP::CMP_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 0x01}, {OPAddr::Acc, 0x01}, {OPAddr::MemABS, 0x02}}, 0x03, OPAddr::Acc, 0x01, 0x80);

    // Zero Page
    nes.testProgram("CMP $00 with [$0000]=1 and ACC=1", {OP::CMP_ZPG, 0x00}, 3, {{OPAddr::Acc, 1}, {OPAddr::MemZeroPage, 1}}, 0x80, OPAddr::Acc, 0x01, 0x03);
    nes.testProgram("CMP $01 with [$0001]=2 and ACC=1", {OP::CMP_ZPG, 0x01}, 3, {{OPAddr::Acc, 1}, {OPAddr::MemZeroPage_1, 2}}, 0x03, OPAddr::Acc, 0x01, 0x80);

    // X-Indexed Zero Page
    nes.testProgram("CMP $00,X with X=1 and [$0001]=1 and ACC=1", {OP::CMP_XZP, 0x00}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 1}, {OPAddr::MemZeroPage_1, 0x01}}, 0x80, OPAddr::Acc, 1, 0x03);
    nes.testProgram("CMP $FF,X with X=1 and [$0000]=2 and ACC=1", {OP::CMP_XZP, 0xFF}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 1}, {OPAddr::MemZeroPage, 0x02}}, 0x03, OPAddr::Acc, 1, 0x80);

    // X-Indexed Zero Page Indirect
    nes.testProgram("CMP ($FF,X) with X=1 and ACC=1 and C=0 and [$0000]=$00 [$0001]=$02 [$0200]=2", {OP::CMP_XZI, 0xFF}, 6, {{OPAddr::Acc, 1}, {OPAddr::X, 1}, {OPAddr::MemZeroPage, 0}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS, 2} }, 0x00, OPAddr::Acc, 1, 0x80);

    // Zero Page Indirect Y-Indexed
    nes.testProgram("CMP ($00),Y with Y=1 and ACC=1 and C=0 and [$0000]=$00 [$0001]=2 [$0201]=2", {OP::CMP_ZIY, 0x00}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 1}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS_1, 2}}, 0x00, OPAddr::Acc, 1, 0x80);
    nes.testProgram("CMP ($00),Y with Y=1 and ACC=1 and C=0 and [$0000]=$FF [$0001]=1 [$0200]=1", {OP::CMP_ZIY, 0x00}, 6, {{OPAddr::Y, 1}, {OPAddr::Acc, 1}, {OPAddr::MemZeroPage, 0xFF}, {OPAddr::MemZeroPage_1, 1}, {OPAddr::MemABS, 1}}, 0x00, OPAddr::Acc, 1, 0x03);
}

SCENARIO("Compare with X register")
{
    NESTest nes;

    // Immediate
    nes.testProgram("CPX #$01 with X = $01", { OP::CPX_IMM, 0x01 }, 2, OPAddr::X, 0x01, 0x80, OPAddr::X, 0x01, 0x03);
    nes.testProgram("CPX #$01 with X = $02", { OP::CPX_IMM, 0x01 }, 2, OPAddr::X, 0x02, 0x82, OPAddr::X, 0x02, 0x01);
    nes.testProgram("CPX #$02 with X = $01", { OP::CPX_IMM, 0x02 }, 2, OPAddr::X, 0x01, 0x03, OPAddr::X, 0x01, 0x80);

    // Absolute
    nes.testProgram("CPX $0200 with [$0200] = $01 and X = $01", { OP::CPX_ABS, 0x00, 0x02 }, 4, { {OPAddr::X, 0x01}, {OPAddr::MemABS, 0x01} }, 0x80, OPAddr::X, 0x01, 0x03);
    nes.testProgram("CPX $0200 with [$0200] = $01 and X = $02", { OP::CPX_ABS, 0x00, 0x02 }, 4, { {OPAddr::X, 0x02}, {OPAddr::MemABS, 0x01} }, 0x82, OPAddr::X, 0x02, 0x01);
    nes.testProgram("CPX $0200 with [$0200] = $02 and X = $01", { OP::CPX_ABS, 0x00, 0x02 }, 4, { {OPAddr::X, 0x01}, {OPAddr::MemABS, 0x02} }, 0x03, OPAddr::X, 0x01, 0x80);

    // Zero Page
    nes.testProgram("CPX $00 with [$0000]=1 and X=1", {OP::CPX_ZPG, 0x00}, 3, {{OPAddr::X, 0x01}, {OPAddr::MemZeroPage, 1}}, 0x80, OPAddr::X, 0x01, 0x03);
    nes.testProgram("CPX $01 with [$0001]=2 and X=1", {OP::CPX_ZPG, 0x01}, 3, {{OPAddr::X, 0x01}, {OPAddr::MemZeroPage_1, 2}}, 0x03, OPAddr::X, 0x01, 0x80);
}

SCENARIO("Compare with Y register")
{
    NESTest nes;

    // Immediate
    nes.testProgram("CPY #$01 with y = $01", { OP::CPY_IMM, 0x01 }, 2, OPAddr::Y, 0x01, 0x80, OPAddr::Y, 0x01, 0x03);
    nes.testProgram("CPY #$01 with y = $02", { OP::CPY_IMM, 0x01 }, 2, OPAddr::Y, 0x02, 0x82, OPAddr::Y, 0x02, 0x01);
    nes.testProgram("CPY #$02 with y = $01", { OP::CPY_IMM, 0x02 }, 2, OPAddr::Y, 0x01, 0x03, OPAddr::Y, 0x01, 0x80);

    // Absolute
    nes.testProgram("CPY $0200 with [$0200] = $01 and y = $01", { OP::CPY_ABS, 0x00, 0x02 }, 4, { {OPAddr::Y, 0x01}, {OPAddr::MemABS, 0x01} }, 0x80, OPAddr::Y, 0x01, 0x03);
    nes.testProgram("CPY $0200 with [$0200] = $01 and y = $02", { OP::CPY_ABS, 0x00, 0x02 }, 4, { {OPAddr::Y, 0x02}, {OPAddr::MemABS, 0x01} }, 0x82, OPAddr::Y, 0x02, 0x01);
    nes.testProgram("CPY $0200 with [$0200] = $02 and y = $01", { OP::CPY_ABS, 0x00, 0x02 }, 4, { {OPAddr::Y, 0x01}, {OPAddr::MemABS, 0x02} }, 0x03, OPAddr::Y, 0x01, 0x80);

    // Zero Page
    nes.testProgram("CPY $00 with [$0000]=1 and Y=1", {OP::CPY_ZPG, 0x00}, 3, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage, 1}}, 0x80, OPAddr::Y, 0x01, 0x03);
    nes.testProgram("CPY $01 with [$0001]=2 and Y=1", {OP::CPY_ZPG, 0x01}, 3, {{OPAddr::Y, 1}, {OPAddr::MemZeroPage_1, 2}}, 0x03, OPAddr::Y, 0x01, 0x80);
}

SCENARIO("Subtract from accumulator with borrow")
{
    NESTest nes;

    // Immediate
    nes.testProgram("SBC #$01 with ACC = 2 and C = 0", { OP::SBC_IMM, 0x01 }, 2, OPAddr::Acc, 0x02, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC #$01 with ACC = 2 and C = 0", { OP::SBC_IMM, 0x01 }, 2, OPAddr::Acc, 0x02, 0xC2, OPAddr::Acc, 0x01, 0x01);
    nes.testProgram("SBC #$03 with ACC = 2 and C = 1", { OP::SBC_IMM, 0x03 }, 2, OPAddr::Acc, 0x02, 0x01, OPAddr::Acc, 0xFF, 0x80);
    nes.testProgram("SBC #$FF with ACC = $7F and C = 1", { OP::SBC_IMM, 0xFF }, 2, OPAddr::Acc, 0x7F, 0x03, OPAddr::Acc, 0x80, 0xC0);
    nes.testProgram("SBC #$01 with ACC = $80 and C = 1", { OP::SBC_IMM, 0x01 }, 2, OPAddr::Acc, 0x80, 0x03, OPAddr::Acc, 0x7F, 0x41);

    // Absolute
    nes.testProgram("SBC $0200 with [$0200] = $01 and ACC = 2 and C = 0", { OP::SBC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC $0200 with [$0200] = $01 and ACC = 2 and C = 0", { OP::SBC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x01}}, 0xC2, OPAddr::Acc, 0x01, 0x01);
    nes.testProgram("SBC $0200 with [$0200] = $03 and ACC = 2 and C = 1", { OP::SBC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x03}}, 0x01, OPAddr::Acc, 0xFF, 0x80);
    nes.testProgram("SBC $0200 with [$0200] = $FF and ACC = $7F and C = 1", { OP::SBC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x7F}, {OPAddr::MemABS, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);
    nes.testProgram("SBC $0200 with [$0200] = $01 and ACC = $80 and C = 1", { OP::SBC_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x80}, {OPAddr::MemABS, 0x01}}, 0x03, OPAddr::Acc, 0x7F, 0x41);

    // X-Indexed Absolute
    nes.testProgram("SBC $0200,X with X=0 and [$0200]=$01 and ACC=$02 and C=0", {OP::SBC_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0}, {OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC $01FF,X with X=1 and [$0200]=$FF and ACC=$7F and C=1", {OP::SBC_XAB, 0xFF, 0x01 }, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemABS, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);

    // Y-Indexed Absolute
    nes.testProgram("SBC $0200,Y with Y=0 and [$0200]=$01 and ACC=$02 and C=0", {OP::SBC_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0}, {OPAddr::Acc, 0x02}, {OPAddr::MemABS, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC $01FF,Y with Y=1 and [$0200]=$FF and ACC=$7F and C=1", {OP::SBC_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemABS, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);

    // Zero Page
    nes.testProgram("SBC $00 with [$0000]=$01 and ACC=2 and C=0", {OP::SBC_ZPG, 0x00}, 3, {{OPAddr::Acc, 0x02}, {OPAddr::MemZeroPage, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC $01 with [$0001]=$FF and ACC=$7F and C=1", {OP::SBC_ZPG, 0x01}, 3, {{OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage_1, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);

    // X-Indexed Zero Page
    nes.testProgram("SBC $00,X with X=1 and [$0001]=$01 and ACC=$02 and C=0", {OP::SBC_XZP, 0x00}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x02}, {OPAddr::MemZeroPage_1, 0x01}}, 0xC0, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("SBC $FF,X with X=1 and [$0000]=$FF and ACC=$7F and C=1", {OP::SBC_XZP, 0xFF}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);

    // X-Indexed Zero Page Indirect
    nes.testProgram("SBC ($FF,X) with X=1 and ACC=$7F and C=1 and [$0000]=$00 [$0001]=$02 [$0200]=$FF", {OP::SBC_XZI, 0xFF}, 6, {{OPAddr::Acc, 0x7F}, {OPAddr::X, 1}, {OPAddr::MemZeroPage, 0}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS, 0xFF} }, 0x03, OPAddr::Acc, 0x80, 0xC0);

    // Zero Page Indirect Y-Indexed
    nes.testProgram("SBC ($00),Y with Y=1 and ACC=$7F and C=1 and [$0000]=$00 [$0001]=$02 [$0201]=$FF", {OP::SBC_ZIY, 0}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 0x00}, {OPAddr::MemZeroPage_1, 2}, {OPAddr::MemABS_1, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);
    nes.testProgram("SBC ($00),Y with Y=1 and ACC=$7F and C=1 and [$0000]=$FF [$0001]=$01 [$0200]=$FF", {OP::SBC_ZIY, 0}, 6, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x7F}, {OPAddr::MemZeroPage, 0xFF}, {OPAddr::MemZeroPage_1, 1}, {OPAddr::MemABS, 0xFF}}, 0x03, OPAddr::Acc, 0x80, 0xC0);
}
