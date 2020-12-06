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
#include <Carbon/Carbon.h>

#include "IODevice.hpp"

class Keyboard : public IODevice
{
private:
    
    uint8_t key  = 0x00;
    uint8_t mask = 0x00;

    std::array<uint8_t, 8> keys {};
    
    static const short None = 1;
    
    const short matrix[8][8] =
    {
        { kVK_Home,   kVK_ANSI_KeypadClear, kVK_Escape,         kVK_F1,               kVK_F2,             kVK_F3,                kVK_F4,          kVK_F5         },
        { kVK_Tab ,   None,                 kVK_Return,         kVK_Delete,           kVK_LeftArrow,      kVK_UpArrow,           kVK_RightArrow,  kVK_DownArrow  },
        { kVK_ANSI_0, kVK_ANSI_1,           kVK_ANSI_2,         kVK_ANSI_3,           kVK_ANSI_4,         kVK_ANSI_5,            kVK_ANSI_6,      kVK_ANSI_7     },
        { kVK_ANSI_8, kVK_ANSI_9,           None,               kVK_ANSI_Semicolon,   kVK_ANSI_Comma,     kVK_ANSI_Minus,        kVK_ANSI_Period, kVK_ANSI_Slash },
        { None,       kVK_ANSI_A,           kVK_ANSI_B,         kVK_ANSI_C,           kVK_ANSI_D,         kVK_ANSI_E,            kVK_ANSI_F,      kVK_ANSI_G     },
        { kVK_ANSI_H, kVK_ANSI_I,           kVK_ANSI_J,         kVK_ANSI_K,           kVK_ANSI_L,         kVK_ANSI_M,            kVK_ANSI_N,      kVK_ANSI_O     },
        { kVK_ANSI_P, kVK_ANSI_Q,           kVK_ANSI_R,         kVK_ANSI_S,           kVK_ANSI_T,         kVK_ANSI_U,            kVK_ANSI_V,      kVK_ANSI_W     },
        { kVK_ANSI_X, kVK_ANSI_Y,           kVK_ANSI_Z,         kVK_ANSI_LeftBracket, kVK_ANSI_Backslash, kVK_ANSI_RightBracket, None,            kVK_Space      }
    };
    
public:

    virtual AddressSpace getSpace() const override;
    void keyevent(unsigned short code, bool isPressed);
    
    virtual uint8_t read (uint16_t address) const override;
    virtual void   write (uint16_t address, uint8_t data) override;
};

#endif /* Keyboard_hpp */
