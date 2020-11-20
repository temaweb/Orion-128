//
//  Memory.hpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef Memory_hpp
#define Memory_hpp

#include <stdio.h>
#include <array>

#include "IODevice.hpp"

class Memory : public IODevice
{
private:
    
    uint8_t page = 0x00;
    std::array<std::array<uint8_t, 60 * 1024>, 4> memory {};
    
public:
    Memory();
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override;
    
    // I/O
    
    virtual uint8_t read (const uint16_t address) const override;
    virtual uint8_t read (const uint16_t address, uint8_t page) const;
    virtual void   write (const uint16_t address, uint8_t data) override;
    
    void   writeB (const uint16_t address, uint8_t data);
    
    void switchPage(uint8_t page);
};

#endif /* Memory_hpp */
