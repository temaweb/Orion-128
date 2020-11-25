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
    uint8_t page = 0x00;
    
public:
    MemorySwitch(std::shared_ptr<Memory> memory) : memory(memory)
    { }
    
    uint8_t getPage()
    {
        return page;
    }

    virtual void write (const uint16_t address, uint8_t data) override
    {
        page = data;
        memory -> switchPage(data & 0x03);
    }
};

#endif /* MemoryController_hpp */
