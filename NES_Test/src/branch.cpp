#include "util.h"

SCENARIO("Branch instructions")
{
    NESTest nes;

    // BCC
    nes.testProgram("BCC $05 with C=1", {OP::BCC_REL, 0x05}, 2, {}, 0x01, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x01); // Not taken
    nes.testProgram("BCC $05 with C=0", {OP::BCC_REL, 0x05}, 3, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x00); // Taken without page cross
    nes.testProgram("BCC $FC with C=0", {OP::BCC_REL, 0xFC}, 4, {}, 0x00, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x00); // Taken with page cross

    // BCS
    nes.testProgram("BCS $05 with C=0", {OP::BCS_REL, 0x05}, 2, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x00); // Not taken
    nes.testProgram("BCS $05 with C=1", {OP::BCS_REL, 0x05}, 3, {}, 0x01, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x01); // Taken without page cross
    nes.testProgram("BCS $FC with C=1", {OP::BCS_REL, 0xFC}, 4, {}, 0x01, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x01); // Taken with page cross

    // BEQ
    nes.testProgram("BEQ $05 with Z=0", {OP::BEQ_REL, 0x05}, 2, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x00); // Not taken
    nes.testProgram("BEQ $05 with Z=1", {OP::BEQ_REL, 0x05}, 3, {}, 0x02, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x02); // Taken without page cross
    nes.testProgram("BEQ $FC with Z=1", {OP::BEQ_REL, 0xFC}, 4, {}, 0x02, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x02); // Taken with page cross

    // BMI
    nes.testProgram("BMI $05 with N=0", {OP::BMI_REL, 0x05}, 2, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x00); // Not taken
    nes.testProgram("BMI $05 with N=1", {OP::BMI_REL, 0x05}, 3, {}, 0x80, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x80); // Taken without page cross
    nes.testProgram("BMI $FC with N=1", {OP::BMI_REL, 0xFC}, 4, {}, 0x80, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x80); // Taken with page cross

    // BNE
    nes.testProgram("BNE $05 with Z=1", {OP::BNE_REL, 0x05}, 2, {}, 0x02, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x02); // Not taken
    nes.testProgram("BNE $05 with Z=0", {OP::BNE_REL, 0x05}, 3, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x00); // Taken without page cross
    nes.testProgram("BNE $FC with Z=0", {OP::BNE_REL, 0xFC}, 4, {}, 0x00, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x00); // Taken with page cross

    // BPL
    nes.testProgram("BPL $05 with N=1", {OP::BPL_REL, 0x05}, 2, {}, 0x80, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x80); // Not taken
    nes.testProgram("BPL $05 with N=0", {OP::BPL_REL, 0x05}, 3, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x00); // Taken without page cross
    nes.testProgram("BPL $FC with N=0", {OP::BPL_REL, 0xFC}, 4, {}, 0x00, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x00); // Taken with page cross

    // BVC
    nes.testProgram("BVC $05 with V=1", {OP::BVC_REL, 0x05}, 2, {}, 0x40, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x40); // Not taken
    nes.testProgram("BVC $05 with V=0", {OP::BVC_REL, 0x05}, 3, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x00); // Taken without page cross
    nes.testProgram("BVC $FC with V=0", {OP::BVC_REL, 0xFC}, 4, {}, 0x00, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x00); // Taken with page cross

    // BVS
    nes.testProgram("BVS $05 with V=0", {OP::BVS_REL, 0x05}, 2, {}, 0x00, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x02}}, 0x00); // Not taken
    nes.testProgram("BVS $05 with V=1", {OP::BVS_REL, 0x05}, 3, {}, 0x40, {{OPAddr::PC_HI, 0x80}, {OPAddr::PC_LO, 0x07}}, 0x40); // Taken without page cross
    nes.testProgram("BVS $FC with V=1", {OP::BVS_REL, 0xFC}, 4, {}, 0x40, {{OPAddr::PC_HI, 0x7F}, {OPAddr::PC_LO, 0xFE}}, 0x40); // Taken with page cross
}
