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

#ifndef IODevice_hpp
#define IODevice_hpp

#include <cstdint>
#include <memory>

#include "AddressSpace.hpp"

class Device
{
public:
    
    // Device should be process data in the space
    virtual AddressSpace getSpace() const
    {
        return
        {
            0x0000,
            0xFFFF
        };
    }
};

// Read-only devices
class RDevice : virtual public Device
{
public:
    virtual uint8_t read(uint16_t address) const = 0;
};

// Write-only devices
class WDevice : virtual public Device
{
public:
    virtual void write(uint16_t address, uint8_t data) = 0;
};

// R/W device
class IODevice : public RDevice, public WDevice
{

};

#endif /* IODevice_hpp */
