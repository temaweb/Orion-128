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
    
    std::array<uint8_t, 61 * 1024> memory;
    
public:
    Memory();
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override;
    
    // I/O
    virtual uint8_t read (const uint16_t address) const override;
    virtual void   write (const uint16_t address, uint8_t data) override;
};

#endif /* Memory_hpp */
