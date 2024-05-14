#pragma once

#include <cstdint>

namespace nes::opcode {

static constexpr uint8_t
    //---/----- x0 ----|----- x2 ----|----- x8 ----|----- x9 ----|----- xA ----|----- xC ----|----- xD ----|----- xE ----|
    /*0x*/ BRK_IMP=0x00,               PHP_IMP=0x08, ORA_IMM=0x09, ASL_ACC=0x0A,               ORA_ABS=0x0D, ASL_ABS=0x0E,
    /*1x*/                             CLC_IMP=0x18, ORA_YAB=0x19,                             ORA_XAB=0x1D, ASL_XAB=0x1E,
    /*2x*/ JSR_ABS=0x20,               PLP_IMP=0x28, AND_IMM=0x29, ROL_ACC=0x2A, BIT_ABS=0x2C, AND_ABS=0x2D, ROL_ABS=0x2E,
    /*3x*/                             SEC_IMP=0x38, AND_YAB=0x39,                             AND_XAB=0x3D, ROL_XAB=0x3E,
    /*4x*/ RTI_IMP=0x40,               PHA_IMP=0x48, EOR_IMM=0x49, LSR_ACC=0x4A, JMP_ABS=0x4C, EOR_ABS=0x4D, LSR_ABS=0x4E,
    /*5x*/                             CLI_IMP=0x58, EOR_YAB=0x59,                             EOR_XAB=0x5D, LSR_XAB=0x5E,
    /*6x*/ RTS_IMP=0x60,               PLA_IMP=0x68, ADC_IMM=0x69, ROR_ACC=0x6A, JMP_IND=0x6C, ADC_ABS=0x6D, ROR_ABS=0x6E,
    /*7x*/                             SEI_IMP=0x78, ADC_YAB=0x79,                             ADC_XAB=0x7D, ROR_XAB=0x7E,
    /*8x*/                             DEY_IMP=0x88,               TXA_IMP=0x8A, STY_ABS=0x8C, STA_ABS=0x8D, STX_ABS=0x8E,
    /*9x*/                             TYA_IMP=0x98, STA_YAB=0x99, TXS_IMP=0x9A,               STA_XAB=0x9D,
    /*Ax*/ LDY_IMM=0xA0, LDX_IMM=0xA2, TAY_IMP=0xA8, LDA_IMM=0xA9, TAX_IMP=0xAA, LDY_ABS=0xAC, LDA_ABS=0xAD, LDX_ABS=0xAE,
    /*Bx*/                             CLV_IMP=0xB8, LDA_YAB=0xB9, TSX_IMP=0xBA, LDY_XAB=0xBC, LDA_XAB=0xBD, LDX_YAB=0xBE,
    /*Cx*/ CPY_IMM=0xC0,               INY_IMP=0xC8, CMP_IMM=0xC9, DEX_IMP=0xCA, CPY_ABS=0xCC, CMP_ABS=0xCD, DEC_ABS=0xCE,
    /*Dx*/                             CLD_IMP=0xD8, CMP_YAB=0xD9,                             CMP_XAB=0xDD, DEC_XAB=0xDE,
    /*Ex*/ CPX_IMM=0xE0,               INX_IMP=0xE8, SBC_IMM=0xE9, NOP_IMP=0xEA, CPX_ABS=0xEC, SBC_ABS=0xED, INC_ABS=0xEE,
    /*Fx*/                             SED_IMP=0xF8, SBC_YAB=0xF9,                             SBC_XAB=0xFD, INC_XAB=0xFE;
}
