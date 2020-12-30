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

void Keyboard::keyevent(int code, bool isPressed)
{
    std::unique_lock lock(mutex);
    
    for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
        if (matrix[i][j] != (Keys) code)
            continue;
            
        if (isPressed)
            matrixKeys[i] |=  (1 << j);
        else
            matrixKeys[i] &= ~(1 << j);
        
        return;
    }
    
    for (int i = 0; i < 8; i++)
    {
        if (extra[i] != (Keys) code)
            continue;
        
        if (isPressed)
            extraKeys |=  (1 << i);
        else
            extraKeys &= ~(1 << i);
        
        break;
    }
}

uint8_t Keyboard::read(uint16_t address) const
{
    std::shared_lock lock(mutex);
    
    switch (address & 0x03)
    {
        case 0:
            return 0x00;
        case 1:
            return getMatrixKeys();
        case 2:
            return getExtraKeys();
        default:
            return 0xFF;
    }
}

void Keyboard::write(uint16_t adrress, uint8_t data)
{
    if ((adrress & 0x03) > 0)
        return;
        
    mask = ~data;
}

uint8_t Keyboard::getMatrixKeys() const
{
    uint8_t value = 0x00;
    uint8_t mask  = this -> mask;
    
    for (int i = 0; i < 8; i++)
    {
        if (mask & 1)
            value |= matrixKeys[i];
        
        mask >>= 1;
    }
    
    return ~value;
}

uint8_t Keyboard::getExtraKeys() const
{
    return ~extraKeys;
}
