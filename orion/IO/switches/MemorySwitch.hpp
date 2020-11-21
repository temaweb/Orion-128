//
//  MemoryController.hpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef MemoryController_hpp
#define MemoryController_hpp

#include "IODevice.hpp"
#include "Memory.hpp"

class MemorySwitch : public WDevice
{
private:
    std::shared_ptr<Memory> memory;
    
public:
    MemorySwitch(std::shared_ptr<Memory> memory) : memory(memory)
    { }

    virtual void write (const uint16_t address, uint8_t data) override
    {
        memory -> switchPage(data & 0x03);
    }
};

#endif /* MemoryController_hpp */
