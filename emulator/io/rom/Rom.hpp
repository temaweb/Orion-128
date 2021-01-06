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

#ifndef Rom_hpp
#define Rom_hpp

#include <fstream>
#include <iostream>
#include <array>

#include "IODevice.hpp"
#include "Environment.hpp"

template<size_t size = 2 * 1024>
class Rom : public RDevice
{
private:
    std::array<uint8_t, size> rom {};
    
public:
    
    static const uint16_t begin = 0xF800;
    static const uint16_t end   = 0xFFFF;
    
    explicit Rom(std::string path)
    {
        auto file = Environment::openBinaryResource(path);
        
        file.read((Environment::bufferType *) rom.begin(), rom.size());
        file.close();
    }

    virtual AddressSpace getSpace() const override
    {
        return { begin, end };
    }
    
    virtual uint8_t read (uint16_t address) const override
    {
        return rom[address];
    }
};

#endif /* Rom_hpp */
