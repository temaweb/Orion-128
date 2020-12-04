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
    setPage(A);
    
    auto video = ram[A].begin();
    auto color = ram[B].begin();
    
    videoRam = std::make_shared<VideoRam>(video, color);
}

void Memory::setPage(Page mode)
{
    page = ram[mode].begin();
}

std::shared_ptr<VideoRam> Memory::getVideoRam() const
{
    return videoRam;
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
    return page[address];
}

void Memory::write (const uint16_t address, uint8_t data)
{
    page[address] = data;
}

void Memory::writeB (uint16_t address, uint8_t data)
{
    ram[B][address] = data;
}
