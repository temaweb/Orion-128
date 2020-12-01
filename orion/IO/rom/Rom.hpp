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
#include <array>

#include "IODevice.hpp"

template<size_t size = 2 * 1024>
class Rom : public RDevice
{
private:
    std::array<uint8_t, size> rom;
    
public:

    Rom(std::string path)
    {
        auto file = open(path);
        char buffer = 0x00;
        
        for (auto & byte : rom)
        {
            if (file.eof())
            {
                byte = 0x00;
            }
            else
            {
                file.read(&buffer, sizeof(buffer));
                byte = buffer;
            }
        }

        file.close();
    }

    virtual AddressSpace getSpace() const override
    {
        return
        {
            0xF800,
            0xFFFF
        };
    }
    
    virtual uint8_t read (uint16_t address) const override
    {
        return rom[address];
    }
    
private:
    
    std::ifstream open(std::string path)
    {
        return std::ifstream(path, std::ios::in | std::ios::binary);
    }
};

#endif /* Rom_hpp */
