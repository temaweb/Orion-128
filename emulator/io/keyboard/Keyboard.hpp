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
#include <shared_mutex>

#include "Keys.hpp"
#include "IODevice.hpp"

class Keyboard : public IODevice
{
private:
    constexpr static Keys matrix[8][8]
    {
        { Keys::Home,  Keys::Clear,  Keys::Escape,  Keys::F1,         Keys::F2,      Keys::F3,      Keys::F4,      Keys::F5    },
        { Keys::Tab,   Keys::F6,     Keys::Return,  Keys::Backspace,  Keys::Left,    Keys::Up,      Keys::Right,   Keys::Down  },
        { Keys::K0,    Keys::K1,     Keys::K2,      Keys::K3,         Keys::K4,      Keys::K5,      Keys::K6,      Keys::K7    },
        { Keys::K8,    Keys::K9,     Keys::Colon,   Keys::Semicolon,  Keys::Comma,   Keys::Minus,   Keys::Period,  Keys::Slash },
        { Keys::At,    Keys::A,      Keys::B,       Keys::C,          Keys::D,       Keys::E,       Keys::F,       Keys::G     },
        { Keys::H,     Keys::I,      Keys::J,       Keys::K,          Keys::L,       Keys::M,       Keys::N,       Keys::O     },
        { Keys::P,     Keys::Q,      Keys::R,       Keys::S,          Keys::T,       Keys::U,       Keys::V,       Keys::W     },
        { Keys::X,     Keys::Y,      Keys::Z,       Keys::BLeft,      Keys::BSlash,  Keys::BRight,  Keys::Circum,  Keys::Space }
    };
    
    constexpr static Keys extra[8]
    {
        Keys::None,
        Keys::None,
        Keys::None,
        Keys::None,
        Keys::None,
        
        Keys::Shift,
        Keys::Control,
        Keys::Alt
    };
    
private:
    uint8_t mask       = 0x00;
    uint8_t extraKeys  = 0x00;
    
    std::array<uint8_t, 8> matrixKeys {};
    mutable std::shared_mutex mutex;
    
private:
    uint8_t getMatrixKeys() const;
    uint8_t getExtraKeys() const;

public:
    void keyevent(int code, bool isPressed);
    
    virtual AddressSpace getSpace() const override;
    virtual uint8_t read (uint16_t address) const override;
    virtual void write (uint16_t address, uint8_t data) override;
};

#endif /* Keyboard_hpp */
