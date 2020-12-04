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

#ifndef VideoRam_hpp
#define VideoRam_hpp

#include <array>

#include "Ram.hpp"
#include "IODevice.hpp"

class VideoRam
{
private:
    constexpr static std::array<AddressSpace, 4> spaces
    {{
        { 0xC000, 0xFFFF }, // Screen #0 (Default)
        { 0x8000, 0xB000 }, // Screen #1
        { 0x4000, 0x7000 }, // Screen #2
        { 0x0000, 0x3000 }  // Screen #3
    }};

    AddressSpace screen;
    
    pagetype::const_iterator frame;
    pagetype::const_iterator color;
    
private:
    void copy (pagetype::const_iterator page, vbuffer::iterator begin) const;
    
public:

    VideoRam (
        pagetype::const_iterator frame,
        pagetype::const_iterator color
    );
    
    void readPixel (vbuffer::iterator buffer) const;
    void readColor (vbuffer::iterator buffer) const;

    void setScreenMode (uint8_t mode);
};

#endif /* VideoRam_hpp */
