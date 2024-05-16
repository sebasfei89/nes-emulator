#pragma once

#include <cstdint>

namespace nes::opcode {

static constexpr uint8_t
    //---/----- x0 ----|----- x1 ----|----- x2 ----|----- x4 ----|----- x5 ----|----- x6 ----|----- x8 ----|----- x9 ----|----- xA ----|----- xC ----|----- xD ----|----- xE ----|
    /*0x*/ BRK_IMP=0x00, ORA_XZI=0x01,                             ORA_ZPG=0x05, ASL_ZPG=0x06, PHP_IMP=0x08, ORA_IMM=0x09, ASL_ACC=0x0A,               ORA_ABS=0x0D, ASL_ABS=0x0E,
    /*1x*/ BPL_REL=0x10, ORA_ZIY=0x11,                             ORA_XZP=0x15, ASL_XZP=0x16, CLC_IMP=0x18, ORA_YAB=0x19,                             ORA_XAB=0x1D, ASL_XAB=0x1E,
    /*2x*/ JSR_ABS=0x20, AND_XZI=0x21,               BIT_ZPG=0x24, AND_ZPG=0x25, ROL_ZPG=0x26, PLP_IMP=0x28, AND_IMM=0x29, ROL_ACC=0x2A, BIT_ABS=0x2C, AND_ABS=0x2D, ROL_ABS=0x2E,
    /*3x*/ BMI_REL=0x30, AND_ZIY=0x31,                             AND_XZP=0x35, ROL_XZP=0x36, SEC_IMP=0x38, AND_YAB=0x39,                             AND_XAB=0x3D, ROL_XAB=0x3E,
    /*4x*/ RTI_IMP=0x40, EOR_XZI=0x41,                             EOR_ZPG=0x45, LSR_ZPG=0x46, PHA_IMP=0x48, EOR_IMM=0x49, LSR_ACC=0x4A, JMP_ABS=0x4C, EOR_ABS=0x4D, LSR_ABS=0x4E,
    /*5x*/ BVC_REL=0x50, EOR_ZIY=0x51,                             EOR_XZP=0x55, LSR_XZP=0x56, CLI_IMP=0x58, EOR_YAB=0x59,                             EOR_XAB=0x5D, LSR_XAB=0x5E,
    /*6x*/ RTS_IMP=0x60, ADC_XZI=0x61,                             ADC_ZPG=0x65, ROR_ZPG=0x66, PLA_IMP=0x68, ADC_IMM=0x69, ROR_ACC=0x6A, JMP_IND=0x6C, ADC_ABS=0x6D, ROR_ABS=0x6E,
    /*7x*/ BVS_REL=0x70, ADC_ZIY=0x71,                             ADC_XZP=0x75, ROR_XZP=0x76, SEI_IMP=0x78, ADC_YAB=0x79,                             ADC_XAB=0x7D, ROR_XAB=0x7E,
    /*8x*/               STA_XZI=0x81,               STY_ZPG=0x84, STA_ZPG=0x85, STX_ZPG=0x86, DEY_IMP=0x88,               TXA_IMP=0x8A, STY_ABS=0x8C, STA_ABS=0x8D, STX_ABS=0x8E,
    /*9x*/ BCC_REL=0x90, STA_ZIY=0x91,               STY_XZP=0x94, STA_XZP=0x95, STX_YZP=0x96, TYA_IMP=0x98, STA_YAB=0x99, TXS_IMP=0x9A,               STA_XAB=0x9D,
    /*Ax*/ LDY_IMM=0xA0, LDA_XZI=0xA1, LDX_IMM=0xA2, LDY_ZPG=0xA4, LDA_ZPG=0xA5, LDX_ZPG=0xA6, TAY_IMP=0xA8, LDA_IMM=0xA9, TAX_IMP=0xAA, LDY_ABS=0xAC, LDA_ABS=0xAD, LDX_ABS=0xAE,
    /*Bx*/ BCS_REL=0xB0, LDA_ZIY=0xB1,               LDY_XZP=0xB4, LDA_XZP=0xB5, LDX_YZP=0xB6, CLV_IMP=0xB8, LDA_YAB=0xB9, TSX_IMP=0xBA, LDY_XAB=0xBC, LDA_XAB=0xBD, LDX_YAB=0xBE,
    /*Cx*/ CPY_IMM=0xC0, CMP_XZI=0xC1,               CPY_ZPG=0xC4, CMP_ZPG=0xC5, DEC_ZPG=0xC6, INY_IMP=0xC8, CMP_IMM=0xC9, DEX_IMP=0xCA, CPY_ABS=0xCC, CMP_ABS=0xCD, DEC_ABS=0xCE,
    /*Dx*/ BNE_REL=0xD0, CMP_ZIY=0xD1,                             CMP_XZP=0xD5, DEC_XZP=0xD6, CLD_IMP=0xD8, CMP_YAB=0xD9,                             CMP_XAB=0xDD, DEC_XAB=0xDE,
    /*Ex*/ CPX_IMM=0xE0, SBC_XZI=0xE1,               CPX_ZPG=0xE4, SBC_ZPG=0xE5, INC_ZPG=0xE6, INX_IMP=0xE8, SBC_IMM=0xE9, NOP_IMP=0xEA, CPX_ABS=0xEC, SBC_ABS=0xED, INC_ABS=0xEE,
    /*Fx*/ BEQ_REL=0xF0, SBC_ZIY=0xF1,                             SBC_XZP=0xF5, INC_XZP=0xF6, SED_IMP=0xF8, SBC_YAB=0xF9,                             SBC_XAB=0xFD, INC_XAB=0xFE;
}
