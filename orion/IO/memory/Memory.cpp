//
//  Memory.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include "Memory.hpp"

Memory::Memory()
{
    for (auto &page : memory)
    {
        for (auto &a : page)
        {
            a = 0x00;
        }
    }
    
    // JMP 0xF800
    memory[0x00][0x0000] = 0xC3;
    memory[0x00][0x0001] = 0x00;
    memory[0x00][0x0002] = 0xF8;
}

void Memory::switchPage(uint8_t page)
{
    this -> page = page;
}

bool Memory::isAccept(uint16_t address) const
{
    return (address >= 0x0000 &&
            address <= 0xEFFF);
}

#pragma mark -
#pragma mark I/O

uint8_t Memory::read (const uint16_t address) const
{
    return memory[page][address];
}

uint8_t Memory::read (const uint16_t address, uint8_t page) const
{
    return memory[page][address];
}

void Memory::write (const uint16_t address, uint8_t data)
{
    memory[page][address] = data;
}


