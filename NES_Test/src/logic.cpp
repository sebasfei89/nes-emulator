#include "util.h"

SCENARIO("OR with accumulator") {
    NESTest nes;

    // Immediate
    nes.testProgram("ORA #$30 with ACC=$03", { OP::ORA_IMM, 0x30 }, 2, OPAddr::Acc, 0x03, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA #$80 with ACC=$03", { OP::ORA_IMM, 0x80 }, 2, OPAddr::Acc, 0x03, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA #$00 with ACC=$00", { OP::ORA_IMM, 0x00 }, 2, OPAddr::Acc, 0x00, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Absolute
    nes.testProgram("ORA $0200 with ACC=$03 and [$0200]=$30", { OP::ORA_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x30} }, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA $0200 with ACC=$03 and [$0200]=$80", { OP::ORA_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x80} }, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA $0200 with ACC=$00 and [$0200]=$00", { OP::ORA_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0x00}, {OPAddr::MemABS, 0x00} }, 0x80, OPAddr::Acc, 0x00, 0x02);

    // X-Indexed Absolute
    nes.testProgram("ORA $0200,X with X=0, ACC=3 and [$0200]=$30", { OP::ORA_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0}, {OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x30} }, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA $0200,X with X=1, ACC=3 and [$0201]=$80", { OP::ORA_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x03}, {OPAddr::MemABS_1, 0x80} }, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA $01FF,X with X=1, ACC=0 and [$0200]=$00", { OP::ORA_XAB, 0xFF, 0x01 }, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0x00}, {OPAddr::MemABS, 0x00} }, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Y-Indexed Absolute
    nes.testProgram("ORA $0200,Y with Y=0, ACC=3 and [$0200]=$30", {OP::ORA_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0}, {OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x30}}, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA $0200,Y with Y=1, ACC=3 and [$0201]=$80", {OP::ORA_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x03}, {OPAddr::MemABS_1, 0x80}}, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA $01FF,Y with Y=1, ACC=0 and [$0200]=$00", {OP::ORA_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x00}, {OPAddr::MemABS, 0x00}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Zero Page
    nes.testProgram("ORA $00 with ACC=$03 and [$0000]=$80", {OP::ORA_ZPG, 0x00}, 3, {{OPAddr::Acc, 0x03}, {OPAddr::MemZeroPage, 0x80}}, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA $01 with ACC=$00 and [$0001]=$00", {OP::ORA_ZPG, 0x01}, 3, {{OPAddr::Acc, 0x00}, {OPAddr::MemZeroPage_1, 0x00}}, 0x80, OPAddr::Acc, 0x00, 0x02);
}

SCENARIO("Exclusive OR with accumulator") {
    NESTest nes;

    // Immediate
    nes.testProgram("EOR #$0F with ACC=$07", { OP::EOR_IMM, 0x0F }, 2, OPAddr::Acc, 0x07, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR #$F0 with ACC=$70", { OP::EOR_IMM, 0xF0 }, 2, OPAddr::Acc, 0x70, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR #$F0 with ACC=$F0", { OP::EOR_IMM, 0xF0 }, 2, OPAddr::Acc, 0xF0, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Absolute
    nes.testProgram("EOR $0200 with ACC=$07 and [$0200]=$0F", { OP::EOR_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0x07}, {OPAddr::MemABS, 0x0F} }, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR $0200 with ACC=$70 and [$0200]=$F0", { OP::EOR_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0x70}, {OPAddr::MemABS, 0xF0} }, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR $0200 with ACC=$F0 and [$0200]=$F0", { OP::EOR_ABS, 0x00, 0x02 }, 4, { {OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0xF0} }, 0x80, OPAddr::Acc, 0x00, 0x02);

    // X-Indexed Absolute
    nes.testProgram("EOR $0200,X with X=0, ACC=$07 and [$0200]=$0F", { OP::EOR_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 0}, {OPAddr::Acc, 0x07}, {OPAddr::MemABS, 0x0F}}, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR $0200,X with X=1, ACC=$70 and [$0201]=$F0", { OP::EOR_XAB, 0x00, 0x02 }, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0x70}, {OPAddr::MemABS_1, 0xF0}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR $01FF,X with X=1, ACC=$F0 and [$0200]=$F0", { OP::EOR_XAB, 0xFF, 0x01 }, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0xF0}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Y-Indexed Absolute
    nes.testProgram("EOR $0200,Y with Y=0, ACC=$07 and [$0200]=$0F", {OP::EOR_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 0}, {OPAddr::Acc, 0x07}, {OPAddr::MemABS, 0x0F}}, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR $0200,Y with Y=1, ACC=$70 and [$0201]=$F0", {OP::EOR_YAB, 0x00, 0x02}, 4, {{OPAddr::Y, 1}, {OPAddr::Acc, 0x70}, {OPAddr::MemABS_1, 0xF0}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR $01FF,Y with Y=1, ACC=$F0 and [$0200]=$F0", {OP::EOR_YAB, 0xFF, 0x01}, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0xF0}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Zero Page
    nes.testProgram("EOR $00 with ACC=$70 and [$0000]=$F0", {OP::EOR_ZPG, 0x00}, 3, {{OPAddr::Acc, 0x70}, {OPAddr::MemZeroPage, 0xF0}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR $01 with ACC=$F0 and [$0001]=$F0", {OP::EOR_ZPG, 0x01}, 3, {{OPAddr::Acc, 0xF0}, {OPAddr::MemZeroPage_1, 0xF0}}, 0x80, OPAddr::Acc, 0x00, 0x02);
}

SCENARIO("AND with accumulator") {
    NESTest nes;

    // Immediate
    nes.testProgram("AND #$03 with ACC=$0F", { OP::AND_IMM, 0x03 }, 2, OPAddr::Acc, 0x0F, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND #$80 with ACC=$FF", { OP::AND_IMM, 0x80 }, 2, OPAddr::Acc, 0xFF, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND #$0F with ACC=$F0", { OP::AND_IMM, 0x0F }, 2, OPAddr::Acc, 0xF0, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Absolute
    nes.testProgram("AND $0200 with ACC=$0F and [$0200]=$03", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x0F}, {OPAddr::MemABS, 0x03} }, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND $0200 with ACC=$FF and [$0200]=$80", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xFF}, {OPAddr::MemABS, 0x80} }, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND $0200 with ACC=$F0 and [$0200]=$0F", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0x0F} }, 0x80, OPAddr::Acc, 0x00, 0x02);

    // X-Indexed Absolute
    nes.testProgram("AND $0200,X with X=0, ACC=$0F and [$0200]=$03", {OP::AND_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 0}, {OPAddr::Acc, 0x0F}, {OPAddr::MemABS, 0x03}}, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND $0200,X with X=1, ACC=$FF and [$0201]=$80", {OP::AND_XAB, 0x00, 0x02}, 4, {{OPAddr::X, 1}, {OPAddr::Acc, 0xFF}, {OPAddr::MemABS_1, 0x80}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND $01FF,X with X=1, ACC=$F0 and [$0200]=$0F", {OP::AND_XAB, 0xFF, 0x01}, 5, {{OPAddr::X, 1}, {OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0x0F}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Y-Indexed Absolute
    nes.testProgram("AND $0200,Y with Y=0, ACC=$0F and [$0200]=$03", { OP::AND_YAB, 0x00, 0x02 }, 4, {{OPAddr::Y, 0}, {OPAddr::Acc, 0x0F}, {OPAddr::MemABS, 0x03}}, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND $0200,Y with Y=1, ACC=$FF and [$0201]=$80", { OP::AND_YAB, 0x00, 0x02 }, 4, {{OPAddr::Y, 1}, {OPAddr::Acc, 0xFF}, {OPAddr::MemABS_1, 0x80}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND $01FF,Y with Y=1, ACC=$F0 and [$0200]=$0F", { OP::AND_YAB, 0xFF, 0x01 }, 5, {{OPAddr::Y, 1}, {OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0x0F}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    // Zero Page
    nes.testProgram("AND $00 with ACC=$FF and [$0000]=$80", {OP::AND_ZPG, 0x00}, 3, {{OPAddr::Acc, 0xFF}, {OPAddr::MemZeroPage, 0x80}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND $01 with ACC=$F0 and [$0001]=$0F", {OP::AND_ZPG, 0x01}, 3, {{OPAddr::Acc, 0xF0}, {OPAddr::MemZeroPage_1, 0x0F}}, 0x80, OPAddr::Acc, 0x00, 0x02);
}

SCENARIO("Test bits with accumulator") {
    NESTest nes;

    // Absolute
    nes.testProgram("BIT $0200 with ACC=$3F and [$0200]=$F0", { OP::BIT_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x3F}, {OPAddr::MemABS, 0xC0}}, 0x00, OPAddr::Acc, 0x3F, 0xC2);
    nes.testProgram("BIT $0200 with ACC=$3F and [$0200]=$3F", { OP::BIT_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x3F}, {OPAddr::MemABS, 0x3F}}, 0x00, OPAddr::Acc, 0x3F, 0x00);

    // Zero Page
    nes.testProgram("BIT $00 with ACC=$3F and [$0000]=$F0", {OP::BIT_ZPG, 0x00}, 3, {{OPAddr::Acc, 0x3F}, {OPAddr::MemZeroPage, 0xC0}}, 0x00, OPAddr::Acc, 0x3F, 0xC2);
    nes.testProgram("BIT $01 with ACC=$3F and [$0001]=$3F", {OP::BIT_ZPG, 0x01}, 3, {{OPAddr::Acc, 0x3F}, {OPAddr::MemZeroPage_1, 0x3F}}, 0x00, OPAddr::Acc, 0x3F, 0x00);
}
