#include "./mos6502.h"

namespace nes {

void MOS6502::opBranchIf(AddressingMode addrMode, Flags flag, uint8_t set) {
	const int8_t signedOffset = readOperand(addrMode);
	if (testFlag(flag) == set) {
		const uint16_t oldPC = mPC;
		mPC = (int)mPC + signedOffset;
		mCyclesUsed += ((oldPC ^ mPC) >> 8) ? 2 : 1;
	}
}

void MOS6502::opBCC(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Carry, 0);
}

void MOS6502::opBCS(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Carry, 1);
}

void MOS6502::opBEQ(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Zero, 1);
}

void MOS6502::opBMI(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Negative, 1);
}

void MOS6502::opBNE(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Zero, 0);
}

void MOS6502::opBPL(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Negative, 0);
}

void MOS6502::opBVC(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Overflow, 0);
}

void MOS6502::opBVS(AddressingMode addrMode) {
	opBranchIf(addrMode, Flags::Overflow, 1);
}

}
