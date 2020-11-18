//
//  Memory.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include "Memory.hpp"

Memory::Memory()
{
    for (auto &a : memory)
    {
        a = 0x00;
    }
    
    // JMP 0xF800
    memory[0x0000] = 0xC3;
    memory[0x0001] = 0x00;
    memory[0x0002] = 0xF8;
}

bool Memory::isAccept(uint16_t address) const
{
    return address >= 0x0000 &&
           address <= 0xF3FF;
}

#pragma mark -
#pragma mark I/O

uint8_t Memory::read (const uint16_t address) const
{
    return memory[address];
}

void Memory::write (const uint16_t address, uint8_t data)
{
    memory[address] = data;
}


