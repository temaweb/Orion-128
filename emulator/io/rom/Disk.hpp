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

#ifndef Disk_hpp
#define Disk_hpp

#include "Rom.hpp"
#include "IODevice.hpp"

class Disk : public IODevice, public Rom<64 * 1024>
{
private:
    uint16_t address = 0x0000;
    
    enum
    {
        LO = 0x01,
        HI = 0x02
    };
    
public:
    Disk() : Rom("rom/Orion128_RomDisk4.rom")
    {}

    virtual AddressSpace getSpace() const override
    {
        return
        {
            0xF500,
            0xF5FF
        };
    }
    
    virtual uint8_t read(uint16_t) const override
    {
        return Rom::read(this -> address);
    }
    
    virtual void write(uint16_t address, uint8_t data) override
    {
        int flag = address & 0x03;
        
        if (flag == LO) {
            this -> address = (this -> address & 0xFF00) | data;
        }
        
        if (flag == HI) {
            this -> address = (this -> address & 0x00FF) | (data << 8);
        }
    }
};

#endif /* Disk_hpp */
