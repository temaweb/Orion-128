//
//  System.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include "System.hpp"

bool System::isAccept(uint16_t address) const
{
    return (address >= 0xF000 &&
            address <= 0xF7FF);
}

#pragma mark -
#pragma mark I/O

uint8_t System::read (const uint16_t address) const
{
    return ram[address];
}

void System::write (const uint16_t address, uint8_t data)
{
    ram[address] = data;
}
