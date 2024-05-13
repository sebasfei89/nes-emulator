#include "util.h"

SCENARIO("Logic instructions")
{
    NESTest nes;

    nes.testProgram("ORA #$30 with ACC = $03", { OP::ORA_IMM, 0x30 }, 2, OPAddr::Acc, 0x03, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA #$80 with ACC = $03", { OP::ORA_IMM, 0x80 }, 2, OPAddr::Acc, 0x03, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA #$00 with ACC = $00", { OP::ORA_IMM, 0x00 }, 2, OPAddr::Acc, 0x00, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("ORA $0200 with ACC = $03 and [$0200] = $30", { OP::ORA_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x30}}, 0x82, OPAddr::Acc, 0x33, 0x00);
    nes.testProgram("ORA $0200 with ACC = $03 and [$0200] = $80", { OP::ORA_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x03}, {OPAddr::MemABS, 0x80}}, 0x02, OPAddr::Acc, 0x83, 0x80);
    nes.testProgram("ORA $0200 with ACC = $00 and [$0200] = $00", { OP::ORA_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x00}, {OPAddr::MemABS, 0x00}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("EOR #$0F with ACC = $07", { OP::EOR_IMM, 0x0F }, 2, OPAddr::Acc, 0x07, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR #$F0 with ACC = $70", { OP::EOR_IMM, 0xF0 }, 2, OPAddr::Acc, 0x70, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR #$F0 with ACC = $F0", { OP::EOR_IMM, 0xF0 }, 2, OPAddr::Acc, 0xF0, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("EOR $0200 with ACC = $07 and [$0200] = $0F", { OP::EOR_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x07}, {OPAddr::MemABS, 0x0F}}, 0x82, OPAddr::Acc, 0x08, 0x00);
    nes.testProgram("EOR $0200 with ACC = $70 and [$0200] = $F0", { OP::EOR_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x70}, {OPAddr::MemABS, 0xF0}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("EOR $0200 with ACC = $F0 and [$0200] = $F0", { OP::EOR_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0xF0}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("AND #$03 with ACC = $0F", { OP::AND_IMM, 0x03 }, 2, OPAddr::Acc, 0x0F, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND #$80 with ACC = $FF", { OP::AND_IMM, 0x80 }, 2, OPAddr::Acc, 0xFF, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND #$0F with ACC = $F0", { OP::AND_IMM, 0x0F }, 2, OPAddr::Acc, 0xF0, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("AND $0200 with ACC = $0F and [$0200] = $03", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x0F}, {OPAddr::MemABS, 0x03}}, 0x82, OPAddr::Acc, 0x03, 0x00);
    nes.testProgram("AND $0200 with ACC = $FF and [$0200] = $80", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xFF}, {OPAddr::MemABS, 0x80}}, 0x02, OPAddr::Acc, 0x80, 0x80);
    nes.testProgram("AND $0200 with ACC = $F0 and [$0200] = $0F", { OP::AND_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0xF0}, {OPAddr::MemABS, 0x0F}}, 0x80, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("BIT $0200 with ACC = $3F and [$0200] = $F0", { OP::BIT_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x3F}, {OPAddr::MemABS, 0xC0}}, 0x00, OPAddr::Acc, 0x3F, 0xC2);
    nes.testProgram("BIT $0200 with ACC = $3F and [$0200] = $3F", { OP::BIT_ABS, 0x00, 0x02 }, 4, {{OPAddr::Acc, 0x3F}, {OPAddr::MemABS, 0x3F}}, 0x00, OPAddr::Acc, 0x3F, 0x00);
}
