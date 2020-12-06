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

#include "Keyboard.hpp"

AddressSpace Keyboard::getSpace() const
{
    return
    {
        0xF400,
        0xF4FF
    };
}

void Keyboard::keyevent(unsigned short code, bool isPressed)
{
    for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
        if (matrix[i][j] != code)
            continue;
            
        if (isPressed)
            keys[i] |= (1 << j);
        else
            keys[i] &= ~(1 << j);
        
        break;
    }
}

uint8_t Keyboard::read(uint16_t) const
{
    uint8_t val  = 0x00;
    uint8_t mask = this -> mask;
    
    for (int i = 0; i < 8; i++)
    {
        if (mask & 1)
            val |= keys[i];
        
        mask >>= 1;
    }
    
    return ~val;
}

void Keyboard::write(uint16_t, uint8_t data)
{
    mask = ~data;
}
