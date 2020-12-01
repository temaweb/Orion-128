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

#ifndef IOBus_hpp
#define IOBus_hpp

#include <map>

#include "IO.hpp"
#include "IODevice.hpp"
#include "DefaultDevice.hpp"

class IOBus : public IODevice, public IO<uint16_t>
{
private:
    template<class T>
    using devicemap = std::map<AddressSpace, std::shared_ptr<T>>;
    
    devicemap<RDevice> rdevices;
    devicemap<WDevice> wdevices;
    
public:
    
    virtual uint8_t read(uint16_t address) const override;
    virtual void write(uint16_t address, uint8_t data) override;

    void insertR  (std::shared_ptr<RDevice>  device);
    void insertW  (std::shared_ptr<WDevice>  device);
    void insertRW (std::shared_ptr<IODevice> device);
    
public:
    
    template<class T, class ...Args>
    void insertR (Args&& ...args)
    {
        insertR(std::make_shared<T>(std::forward<Args>(args)...));
    }
    
    template<class T, class ...Args>
    void insertW (Args&& ...args)
    {
        insertW(std::make_shared<T>(std::forward<Args>(args)...));
    }
    
    template<class T, class ...Args>
    void insertRW (Args&& ...args)
    {
        insertRW(std::make_shared<T>(std::forward<Args>(args)...));
    }
    
private:
    
    template<class T>
    const std::shared_ptr<T> & getDevice(uint16_t address, const devicemap<T> & map) const
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
    
    template<class T, class D>
    void insert(devicemap<T> & map, std::shared_ptr<T> device)
    {
        auto decorator = std::make_shared<D>(device);
        map.emplace(device -> getSpace(), decorator);
    }
};

#endif /* IOBus_hpp */
