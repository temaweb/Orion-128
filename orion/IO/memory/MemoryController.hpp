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

class MemorySwitcher : public WDevice
{
private:
    
    static const uint16_t begin = 0xF900;
    static const uint16_t end   = 0xF9FF;
    
private:
    uint8_t page = 0x00;
    std::shared_ptr<Memory> memory;
    
public:
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= begin && address <= end;
    }
    
    // I/O
    virtual void write (const uint16_t address, uint8_t data) override
    {
        memory -> switchPage(data & 0x03);
    }
    
    void connect(std::shared_ptr<Memory> memory)
    {
        this -> memory = memory;
    }
};

#endif /* MemoryController_hpp */
