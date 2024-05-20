#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace nes {
	class IBusListener {
public:
    virtual ~IBusListener() = default;

    virtual bool onHandleWrite(uint16_t addr, uint8_t value) = 0;
    virtual bool onHandleRead(uint16_t addr, uint8_t &value) = 0;
};

using IBusListenerPtr = std::shared_ptr<IBusListener>;

class Bus {
public:
    uint8_t read(uint16_t addr) {
        uint8_t data = 0xFE;
        for (IBusListenerPtr& listener : mListeners)
        {
            if (listener->onHandleRead(addr, data))
                break;
        }
        return data;
    }

    void write(uint16_t addr, uint8_t data) {
        for (IBusListenerPtr& listener : mListeners)
        {
            if (listener->onHandleWrite(addr, data))
                break;
        }
    }

    void connect(IBusListenerPtr listener) {
        mListeners.push_back(listener);
    }

private:
    std::vector<IBusListenerPtr> mListeners;
};

}
