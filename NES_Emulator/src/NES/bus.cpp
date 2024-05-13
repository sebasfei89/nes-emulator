#include "./nes.h"

namespace nes {

void Bus::connect(std::shared_ptr<MOS6502> cpu) {
    if (mCpu) mCpu->onDisconnect();
    mCpu = cpu;
    if (mCpu) mCpu->onConnect(this);
}

void Bus::connect(std::shared_ptr<Cartridge> cartridge) {
    if (mCartridge) mCartridge->onDisconnect();
    mCartridge = cartridge;
    if (mCartridge) mCartridge->onConnect(this);
}

}
