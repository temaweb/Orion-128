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

#include "Memory.hpp"
#include "IODevice.hpp"

class VideoRam
{
public:
    typedef std::array<uint8_t, 12 * 1024> buffer;
    
private:
    std::shared_ptr<const Memory> memory;
    std::array<AddressSpace, 4> screenSpaces
    {{
        { 0xC000, 0xEFFF }, // Screen #0 (Default)
        { 0x8000, 0xAFFF }, // Screen #1
        { 0x4000, 0x6FFF }, // Screen #2
        { 0x0000, 0x2FFF }  // Screen #3
    }};
    
    uint8_t screen = 0x00;
    
public:
    
    VideoRam(std::shared_ptr<const Memory> memory);
    
    void readFrame (uint8_t * begin) const;
    void readColor (uint8_t * begin) const;

    void setScreenMode (uint8_t mode);
    
private:
    void copy (uint8_t * begin, uint8_t page) const;
};

#endif /* VideoRam_hpp */
