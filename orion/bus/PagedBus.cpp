//
//  OrionBus.cpp
//  orion
//
//  Created by Артём Оконечников on 12.11.2020.
//

#include "PagedBus.hpp"

PagedBus::PagedBus()
{
    for (auto &bank : ram)
    {
        bank = std::array<uint8_t, 64 * 1024>();
        
        for (auto &b : bank) {
            b = 0x00;
        }
    }
}

uint8_t PagedBus::read(const uint16_t address) const 
{
    if (address >= 0xF000 && address <= 0xFFFF)
        return ram[monitor][address];
    
    return ram[page][address];
}

void PagedBus::write (const uint16_t address, uint8_t data)
{
    if (address == sysport) {
        page = (data & 0x03);
    }
    
    if (address >= 0xF000 && address <= 0xFFFF)
    {
        ram[monitor][address] = data;
        return;
    }
    
    ram[page][address] = data;
}
