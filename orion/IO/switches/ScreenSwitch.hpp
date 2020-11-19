//
//  DisplaySwitcher.h
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef DisplaySwitcher_h
#define DisplaySwitcher_h

#include "IODevice.hpp"

class ScreenSwitch : public WDevice
{
public:
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= 0xFA00 &&
               address <= 0xFAFF;
    }
    
    // I/O
    virtual void write (const uint16_t address, uint8_t data) override
    {
        // (~value & 0x3) << 14
    }
};

#endif /* DisplaySwitcher_h */
