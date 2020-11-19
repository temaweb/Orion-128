//
//  MemoryController.hpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef MemoryController_hpp
#define MemoryController_hpp

#include <stdio.h>
#include "IODevice.hpp"
#include "Memory.hpp"

class MemorySwitch : public WDevice
{
private:
    uint8_t page = 0x00;
    std::shared_ptr<Memory> memory;
    
public:
    
    void connect(std::shared_ptr<Memory> memory)
    {
        this -> memory = memory;
    }
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= 0xF900 &&
               address <= 0xF9FF;
    }
    
    // I/O
    virtual void write (const uint16_t address, uint8_t data) override
    {
        memory -> switchPage(data & 0x03);
    }
};

#endif /* MemoryController_hpp */
