#include "util.h"

SCENARIO("Load instructions")
{
    NESTest nes;

    nes.testProgram("LDA #$11", { OP::LDA_IMM, 0x11 }, 2, OPAddr::Acc, 0x00, 0x82, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA #$81", { OP::LDA_IMM, 0x81 }, 2, OPAddr::Acc, 0x00, 0x00, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA #$00", { OP::LDA_IMM, 0x00 }, 2, OPAddr::Acc, 0xFF, 0x00, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("LDA $0200 with [$0200] = $11", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::Acc, 0x11, 0x00);
    nes.testProgram("LDA $0200 with [$0200] = $81", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::Acc, 0x81, 0x80);
    nes.testProgram("LDA $0200 with [$0200] = $00", { OP::LDA_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::Acc, 0x00, 0x02);

    nes.testProgram("LDX #$11", { OP::LDX_IMM, 0x11 }, 2, OPAddr::X, 0x00, 0x82, OPAddr::X, 0x11, 0x00);
    nes.testProgram("LDX #$81", { OP::LDX_IMM, 0x81 }, 2, OPAddr::X, 0x00, 0x00, OPAddr::X, 0x81, 0x80);
    nes.testProgram("LDX #$00", { OP::LDX_IMM, 0x00 }, 2, OPAddr::X, 0xFF, 0x00, OPAddr::X, 0x00, 0x02);

    nes.testProgram("LDX $0200 with [$0200] = $11", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::X, 0x11, 0x00);
    nes.testProgram("LDX $0200 with [$0200] = $81", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::X, 0x81, 0x80);
    nes.testProgram("LDX $0200 with [$0200] = $00", { OP::LDX_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::X, 0x00, 0x02);

    nes.testProgram("LDY #$11", { OP::LDY_IMM, 0x11 }, 2, OPAddr::Y, 0x00, 0x82, OPAddr::Y, 0x11, 0x00);
    nes.testProgram("LDY #$81", { OP::LDY_IMM, 0x81 }, 2, OPAddr::Y, 0x00, 0x00, OPAddr::Y, 0x81, 0x80);
    nes.testProgram("LDY #$00", { OP::LDY_IMM, 0x00 }, 2, OPAddr::Y, 0xFF, 0x00, OPAddr::Y, 0x00, 0x02);

    nes.testProgram("LDY $0200 with [$0200] = $11", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x11, 0x82, OPAddr::Y, 0x11, 0x00);
    nes.testProgram("LDY $0200 with [$0200] = $81", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x81, 0x00, OPAddr::Y, 0x81, 0x80);
    nes.testProgram("LDY $0200 with [$0200] = $00", { OP::LDY_ABS, 0x00, 0x02 }, 4, OPAddr::MemABS, 0x00, 0x00, OPAddr::Y, 0x00, 0x02);
}

SCENARIO("Store instructions")
{
    NESTest nes;

    nes.testProgram("STA $0200 with ACC = 0x8F", { OP::STA_ABS, 0x00, 0x02 }, 4, OPAddr::Acc, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STA $0200 with ACC = 0x00", { OP::STA_ABS, 0x00, 0x02 }, 4, OPAddr::Acc, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);

    nes.testProgram("STX $0200 with ACC = 0x8F", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STX $0200 with ACC = 0x00", { OP::STX_ABS, 0x00, 0x02 }, 4, OPAddr::X, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);

    nes.testProgram("STY $0200 with ACC = 0x8F", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x8F, 0x00, OPAddr::MemABS, 0x8F, 0x00);
    nes.testProgram("STY $0200 with ACC = 0x00", { OP::STY_ABS, 0x00, 0x02 }, 4, OPAddr::Y, 0x00, 0x00, OPAddr::MemABS, 0x00, 0x00);
}
