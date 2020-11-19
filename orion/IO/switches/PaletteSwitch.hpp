//
//  ColorSwitcher.h
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef ColorSwitcher_h
#define ColorSwitcher_h

#include <stdio.h>
#include "IODevice.hpp"

class PaletteSwitch : public WDevice
{
public:
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= 0xF800 &&
               address <= 0xF8FF;
    }
    
    // I/O
    virtual void write (const uint16_t address, uint8_t data) override
    {
        // data & 0x03;
    }
};

#endif /* ColorSwitcher_h */
