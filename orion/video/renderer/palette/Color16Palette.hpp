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

#ifndef Color16Palette_hpp
#define Color16Palette_hpp

#include <array>
#include "Palette.hpp"

class Color16Palette : public Palette
{
private:
    
    // Orion memory format color for
    // background and foreground
    //
    // HI nibble - background color
    // LO nibble - foreground color
    uint8_t color = 0x0000;
    
    
    // Orion 16 color palette
    constexpr static std::array<uint32_t, 16> palette
    {
        0x000000, // Black
        0x0000FF, // Blue
        0x008000, // Green
        0x30D5C8, // Turquoise
        0xFF0000, // Red
        0xC400AB, // Magenta
        0x964B00, // Brown
        0xD3D3D3, // Light gray
        0x000000, // Black
        0x00BFFF, // Light blue
        0x99ff99, // Light green
        0x24F2EF, // Light turquoise
        0xFFCBDB, // Pink
        0xD95CC9, // Light magenta
        0xFFFF00, // Yellow
        0xFFFFFF  // White
    };

private:
    Pixel getPixel(uint8_t code) const;
    
public:
    Color16Palette(uint8_t color);
    
    virtual Pixel getBackground() const override;
    virtual Pixel getForeground() const override;
};

#endif /* Color16Palette_hpp */
