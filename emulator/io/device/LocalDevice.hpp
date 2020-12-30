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

#ifndef LocalDevice_hpp
#define LocalDevice_hpp

#include "IODevice.hpp"

template <typename T>
class LocalDevice : public Device
{
private:
    AddressSpace space;
    std::shared_ptr<T> device;

protected:
    const std::shared_ptr<T> & getDevice() const
    {
        return device;
    }
    
    uint16_t getLocal(uint16_t address) const
    {
        return space.getLocal(address);
    }
    
public:
    LocalDevice(std::shared_ptr<T> device) : device(device)
    {
        space = device -> getSpace();
    }
    
    virtual AddressSpace getSpace() const override final
    {
        return space;
    }
};

#endif /* LocalDevice_hpp */
