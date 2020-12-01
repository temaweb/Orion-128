/*
 * This file is part of the Orion-128 distribution (https://github.com/temaweb/orion-128).
 * Copyright (c) 2020 Artem Okonechnikov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Memory.hpp"

Memory::Memory()
{
    // JMP to 0xF800
    memory[0x00][0x0000] = 0xC3;
    memory[0x00][0x0001] = 0x00;
    memory[0x00][0x0002] = 0xF8;
}

void Memory::switchPage(uint8_t page)
{
    this -> page = page;
}

AddressSpace Memory::getSpace() const
{
    return
    {
        0x0000,
        0xEFFF
    };
}

uint8_t Memory::read (const uint16_t address) const
{
    return read(address, page);
}

uint8_t Memory::read (const uint16_t address, uint8_t page) const
{
    return memory[page][address];
}

void Memory::write (const uint16_t address, uint8_t data)
{
    write(address, data, page);
}

void Memory::write (const uint16_t address, uint8_t data, uint8_t page)
{
    memory[page][address] = data;
}

std::array<uint8_t, 12 * 1024> Memory::getFrameBuffer() const
{
    return getVideoBuffer(0x00);
}

std::array<uint8_t, 12 * 1024> Memory::getColorBuffer() const
{
    return getVideoBuffer(0x01);
}

std::array<uint8_t, 12 * 1024> Memory::getVideoBuffer(uint8_t page) const
{
    std::array<uint8_t, 12 * 1024> tmp;
    
    auto begin = memory[page].begin();
    auto end   = memory[page].end();
    
    std::copy (begin + video, end, tmp.begin());
    
    return tmp;
}
