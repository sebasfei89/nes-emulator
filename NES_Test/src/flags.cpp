#include "util.h"

SCENARIO("Clear/Set flag instructions")
{
    NESTest nes;

    nes.testProgram("CLC", { OP::CLC_IMP }, 2, {}, 0xDF, {}, 0xDE);
    nes.testProgram("CLD", { OP::CLD_IMP }, 2, {}, 0xDF, {}, 0xD7);
    nes.testProgram("CLI", { OP::CLI_IMP }, 2, {}, 0xDF, {}, 0xDB);
    nes.testProgram("CLV", { OP::CLV_IMP }, 2, {}, 0xDF, {}, 0x9F);

    nes.testProgram("SEC", { OP::SEC_IMP }, 2, {}, 0x00, {}, 0x01);
    nes.testProgram("SED", { OP::SED_IMP }, 2, {}, 0x00, {}, 0x08);
    nes.testProgram("SEI", { OP::SEI_IMP }, 2, {}, 0x00, {}, 0x04);
}
