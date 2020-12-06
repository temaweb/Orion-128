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

#ifndef IOStorage_hpp
#define IOStorage_hpp

#include <map>

#include "IODevice.hpp"
#include "LocalRDevice.hpp"
#include "LocalWDevice.hpp"

#include "DefaultDevice.hpp"

template<class T, class D>
class IOStorage
{
private:
    std::map<AddressSpace, std::shared_ptr<T>> map;
    
public:
    const std::shared_ptr<T> & getDevice(uint16_t address) const
    {
        for (auto const & [space, device] : map)
        {
            if (address < space.from)
                continue;

            if (address <= space.to)
                return device;
        }

        return DefaultDevice::getInstance<T>();
    }

    void addDevice(std::shared_ptr<T> device)
    {
        auto local = std::make_shared<D>(device);
        map.emplace(device -> getSpace(), local);
    }
};

class IORStorage : public IOStorage<RDevice, LocalRDevice>, public RDevice
{
public:
    virtual uint8_t read(uint16_t address) const override;
};

class IOWStorage : public IOStorage<WDevice, LocalWDevice>, public WDevice
{
public:
    virtual void write(uint16_t address, uint8_t data) override;
};

#endif /* IOStorage_hpp */
