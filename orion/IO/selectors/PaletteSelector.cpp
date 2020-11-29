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

#include "PaletteSelector.hpp"

Space PaletteSelector::getSpace() const
{
    return
    {
        0xF800,
        0xF8FF
    };
}

void PaletteSelector::write (uint16_t, uint8_t data)
{
    // - - 0  Palette #1
    // - - 1  Palette #2
    // - 0 -  Mode #1 / 16 colors
    // - 1 -  Mode #2 / 4 colors
    // 0 - -  Monochrome mode
    // 1 - -  Color mode
    
    video -> switchColorMode(data & 0x7);
}
