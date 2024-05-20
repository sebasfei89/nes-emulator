#include "util.h"

SCENARIO("Stack instructions")
{
    NESTest nes;

    // PUSH
    nes.testProgram("PHA with ACC=$13", {OP::PHA_IMP}, 3, OPAddr::Acc, 0x13, 0x00, {{OPAddr::MemSTK_0, 0x13}, {OPAddr::SP, 0xFE}}, 0x00);
    nes.testProgram("PHP", {OP::PHP_IMP}, 3, {}, 0xCF, {{OPAddr::MemSTK_0, 0xFF}, {OPAddr::SP, 0xFE}}, 0xCF);
    
    // PULL
    nes.testProgram("PLA with STK=[$81]", {OP::PLA_IMP}, 4, {{OPAddr::SP, 0xFE}, {OPAddr::MemSTK_0, 0x81}}, 0x02, {{OPAddr::Acc, 0x81}, {OPAddr::SP, 0xFF}}, 0x80);
    nes.testProgram("PLA with STK=[$00]", {OP::PLA_IMP}, 4, {{OPAddr::SP, 0xFE}, {OPAddr::MemSTK_0, 0x00}}, 0x80, {{OPAddr::Acc, 0x00}, {OPAddr::SP, 0xFF}}, 0x02);
    nes.testProgram("PLP with STK=[$DF]", {OP::PLP_IMP}, 4, {{OPAddr::SP, 0xFE}, {OPAddr::MemSTK_0, 0xCF}}, 0x30, OPAddr::SP, 0xFF, 0xFF);
}
