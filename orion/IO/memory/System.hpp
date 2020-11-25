//
//  System.hpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef System_hpp
#define System_hpp

#include <stdio.h>
#include <cstdint>
#include <array>

#include "IODevice.hpp"

class System : public IODevice
{
private:
    
    std::array<uint8_t, 2 * 1024> ram {};
    
public:
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override;
    
    // I/O
    virtual uint8_t read (const uint16_t address) const override;
    virtual void   write (const uint16_t address, uint8_t data) override;
};

#endif /* System_hpp */
