//
//  Bus.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include "Bus.hpp"

Bus::Bus()
{
    for (auto &a : ram)
    {
        a = 0x00;
    }
}

uint8_t Bus::read(uint16_t offset) const
{
    if (offset >= 0x00 && offset <= 0xFFFF)
        return ram[offset];
    
    return 0x00;
}

void Bus::write(uint16_t offset, uint8_t data)
{
    if (offset >= 0x00 && offset <= 0xFFFF)
        ram[offset] = data;
}
