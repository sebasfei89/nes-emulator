#include "util.h"

#include <fstream>

SCENARIO("NES test rom") {
	std::ifstream romFile("./assets/6502_functional_test.bin", std::ios::binary);
	REQUIRE(romFile.good());

	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(romFile), {});
	auto ram = std::make_shared<nes::Ram<65536>>();
	ram->load(0x000A, std::span{ buffer });

	nes::MOS6502 cpu;
	cpu.bus().connect(ram);
	cpu.reset();

	size_t cyclesUsed;
	const uint16_t pcAddr = cpu.runTillInfiniteLoop(0x0400, cyclesUsed);
	CHECK(pcAddr == 0x336D);
	CHECK(cyclesUsed == 84030451);
}
