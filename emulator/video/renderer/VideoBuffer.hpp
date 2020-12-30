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

#ifndef VideoBuffer_hpp
#define VideoBuffer_hpp

#include "Ram.hpp"

struct VideoBuffer
{
    vbuffer pixels {};
    vbuffer colors {};
    
    vbuffer::iterator getPixelsIterator();
    vbuffer::iterator getColorsIterator();
    
    bool operator==(const VideoBuffer & buffer) const;
    bool operator!=(const VideoBuffer & buffer) const;
    
    uint8_t readFrame(uint16_t address) const;
    uint8_t readColor(uint16_t address) const;
};

#endif /* VideoBuffer_hpp */
