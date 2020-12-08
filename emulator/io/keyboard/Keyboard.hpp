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

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <array>

#include "Keys.hpp"
#include "IODevice.hpp"

class Keyboard : public IODevice
{
private:
    
    uint8_t key  = 0x00;
    uint8_t mask = 0x00;

    std::array<uint8_t, 8> keys {};
    
    constexpr static int matrix[8][8] =
    {
        {    Home,     Clear,    Escape,    F1,           F2,        F3,        F4,        F5       },
        {    Tab,      F6,       Return,    Backspace,    Left,      Up,        Right,     Down     },
        {    K0,       K1,       K2,        K3,           K4,        K5,        K6,        K7       },
        {    K8,       K9,       Colon,     Semicolon,    Comma,     Minus,     Period,    Slash    },
        {    At,       A,        B,         C,            D,         E,         F,         G        },
        {    H,        I,        J,         K,            L,         M,         N,         O        },
        {    P,        Q,        R,         S,            T,         U,         V,         W        },
        {    X,        Y,        Z,         BLeft,        BSlash,    BRight,    Circum,    Space    }
    };
    
public:
    void keyevent(int code, bool isPressed);
    
    virtual AddressSpace getSpace() const override;
    virtual uint8_t read (uint16_t address) const override;
    virtual void write (uint16_t address, uint8_t data) override;
};

#endif /* Keyboard_hpp */
