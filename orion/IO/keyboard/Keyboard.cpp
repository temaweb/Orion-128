//
//  Keyboard.cpp
//  orion
//
//  Created by Артём Оконечников on 15.11.2020.
//

#include "Keyboard.hpp"

#include <iostream>
#include <iomanip>

Keyboard::Keyboard()
{
    for (auto & item : keys)
    {
        item = 0x00;
    }
}

void Keyboard::keyevent(unsigned short code, bool isPressed)
{
    for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
        if (matrix[i][j] == code)
        {
            if (isPressed)
                keys[i] |= (1 << j);
            else
                keys[i] &= ~(1 << j);
            
            break;
        }
    }
}

bool Keyboard::isAccept(uint16_t address) const
{
    return address >= 0xF400 &&
           address <= 0xF4FF;
}

#pragma mark -
#pragma mark IO

uint8_t Keyboard::read(const uint16_t address) const
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

void Keyboard::write(const uint16_t address, uint8_t data)
{
    mask = ~data;
}
