#include "./mos6502.h"

namespace nes {

void MOS6502::opLDA(AddressingMode addrMode) {
    mA = readOperand(addrMode);
    updateNZStatusFlags(mA);
}

void MOS6502::opSTA(AddressingMode addrMode) {
    writeResult(addrMode, mA);
}

void MOS6502::opLDX(AddressingMode addrMode) {
    mX = readOperand(addrMode);
    updateNZStatusFlags(mX);
}

void MOS6502::opSTX(AddressingMode addrMode) {
    writeResult(addrMode, mX);
}

void MOS6502::opLDY(AddressingMode addrMode) {
    mY = readOperand(addrMode);
    updateNZStatusFlags(mY);
}

void MOS6502::opSTY(AddressingMode addrMode) {
    writeResult(addrMode, mY);
}

}
