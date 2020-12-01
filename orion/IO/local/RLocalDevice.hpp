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

#ifndef RLocalDevice_hpp
#define RLocalDevice_hpp

#include "LocalDevice.hpp"

class RLocalDevice final : public LocalDevice<RDevice>, public RDevice
{
public:
    RLocalDevice(std::shared_ptr<RDevice> device) : LocalDevice(device)
    { }
    
    virtual uint8_t read(uint16_t address) const override
    {
        auto local = getLocal(address);
        return device -> read(local);
    }
};

#endif /* RLocalDevice_hpp */
