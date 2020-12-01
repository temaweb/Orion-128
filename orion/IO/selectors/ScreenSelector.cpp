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

#include "ScreenSelector.hpp"

AddressSpace ScreenSelector::getSpace() const
{
    return
    {
        0xFA00,
        0xFAFF
    };
}

void ScreenSelector::write (uint16_t, uint8_t data)
{
    // - 0 0  Screen #0 (0xС000 — 0xEFFF)
    // - 0 1  Screen #1 (0x8000 — 0xAFFF)
    // - 1 0  Screen #2 (0x4000 — 0x6FFF)
    // - 1 1  Screen #3 (0x0000 — 0x2FFF)
    
    video -> switchScreenMode(data & 0x3);
}
