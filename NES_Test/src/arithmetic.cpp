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
}
