#include "util.h"

SCENARIO("Shift instructions")
{
    NESTest nes;

    nes.testProgram("ASL with ACC = 0x80", { OP::ASL_ACC }, 2, OPAddr::Acc, 0x80, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ASL with ACC = 0x41", { OP::ASL_ACC }, 2, OPAddr::Acc, 0x41, 0x03, OPAddr::Acc, 0x82, 0x80);

    nes.testProgram("ASL $0200 with [$0200] = 0x80", { OP::ASL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ASL $0200 with [$0200] = 0x41", { OP::ASL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x41, 0x00, OPAddr::MemABS, 0x82, 0x80);

    nes.testProgram("LSR with ACC = 0x01", { OP::LSR_ACC }, 2, OPAddr::Acc, 0x01, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("LSR with ACC = 0x80", { OP::LSR_ACC }, 2, OPAddr::Acc, 0x80, 0x83, OPAddr::Acc, 0x40, 0x00);

    nes.testProgram("LSR $0200 with [$0200] = 0x01", { OP::LSR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("LSR $0200 with [$0200] = 0x80", { OP::LSR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x83, OPAddr::MemABS, 0x40, 0x00);

    nes.testProgram("ROL with ACC = 0x80 and C = 0", { OP::ROL_ACC }, 2, OPAddr::Acc, 0x80, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ROL with ACC = 0x40 and C = 1", { OP::ROL_ACC }, 2, OPAddr::Acc, 0x40, 0x03, OPAddr::Acc, 0x81, 0x80);

    nes.testProgram("ROL $2000 with [$2000] = 0x80 and C = 0", { OP::ROL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x80, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROL $2000 with [$2000] = 0x40 and C = 1", { OP::ROL_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x40, 0x03, OPAddr::MemABS, 0x81, 0x80);

    nes.testProgram("ROR with ACC = 0x01 and C = 0", { OP::ROR_ACC }, 2, OPAddr::Acc, 0x01, 0x80, OPAddr::Acc, 0x00, 0x03);
    nes.testProgram("ROR with ACC = 0x02 and C = 1", { OP::ROR_ACC }, 2, OPAddr::Acc, 0x02, 0x03, OPAddr::Acc, 0x81, 0x80);

    nes.testProgram("ROR $2000 with [$2000] = 0x01 and C = 0", { OP::ROR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x01, 0x80, OPAddr::MemABS, 0x00, 0x03);
    nes.testProgram("ROR $2000 with [$2000] = 0x02 and C = 1", { OP::ROR_ABS, 0x00, 0x02 }, 6, OPAddr::MemABS, 0x02, 0x03, OPAddr::MemABS, 0x81, 0x80);
}
