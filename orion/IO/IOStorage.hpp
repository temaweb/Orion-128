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

#include <memory>
#include <map>

#include "IODevice.hpp"

class IOStorage : public Device
{
private:
    
    template<class T>
    using devmap = std::map<Space, std::shared_ptr<T>>;
    
    devmap<RDevice> rdevices;
    devmap<WDevice> wdevices;
    
private:
    
    template<class T>
    void insert(devmap<T> & map, std::shared_ptr<T> device)
    {
        map.emplace(device -> getSpace(), device);
    }
    
    template<class T>
    std::shared_ptr<T> getDevice(uint16_t address, const devmap<T> & map) const
    {
        if (isAccept(address))
        {
            for (auto const & [space, device] : map)
            {
                if (device -> isAccept(address))
                    return device;
            }
        }
        
        return defaultDevice();
    }
    
public:
    
    virtual std::shared_ptr<IODevice> defaultDevice() const;
    
    void insertR  (std::shared_ptr<RDevice>  device);
    void insertW  (std::shared_ptr<WDevice>  device);
    void insertRW (std::shared_ptr<IODevice> device);
    
    std::shared_ptr<RDevice> getRDevice (uint16_t address) const;
    std::shared_ptr<WDevice> getWDevice (uint16_t address) const;
    
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
};

#endif /* IOStorage_hpp */
