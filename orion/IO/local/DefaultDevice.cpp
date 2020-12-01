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

#ifdef DEBUG
    #include <inttypes.h>
#endif

#include "DefaultDevice.hpp"

uint8_t DefaultDevice::read(uint16_t address) const
{
#ifdef DEBUG
    printf("Read from default device: 0x%.4X\n", address);
#endif
    
    return value;
}

void DefaultDevice::write(uint16_t address, uint8_t data)
{
#ifdef DEBUG
    printf("Write to default device: 0x%.4X $%.2X\n", address, data);
#endif
}
