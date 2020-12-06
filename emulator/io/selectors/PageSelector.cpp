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

#include "PageSelector.hpp"

AddressSpace PageSelector::getSpace() const
{
    return
    {
        0xF900,
        0xF9FF
    };
}

void PageSelector::write (uint16_t, uint8_t data)
{
    // - 0 0  general page    #0
    // - 0 1  additional page #1
    // - 1 0  additional page #2
    // - 1 1  additional page #3
    
    memory -> setPage((Memory::Page)(data & 0x03));
}
