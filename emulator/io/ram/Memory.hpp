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

#ifndef Memory_hpp
#define Memory_hpp

#include <array>

#include "Ram.hpp"
#include "VideoRam.hpp"
#include "IODevice.hpp"

class Memory : public IODevice
{
private:
    std::array<pagetype, 4> ram {};
    std::shared_ptr<VideoRam> videoRam;
    pagetype::iterator page;
    
    enum Page
    {
        A = 0x00,
        B = 0x01,
        C = 0x02,
        D = 0x03
    };
    
public:
    Memory();
    
    void setPage (uint8_t page);
    const std::shared_ptr<VideoRam> & getVideoRam() const;
    
// I/O
public:
    
    virtual AddressSpace getSpace() const override;
    virtual uint8_t read (uint16_t address) const override;
    virtual void write   (uint16_t address, uint8_t data) override;
    
    // Write to second memory page direct
    void writeB  (uint16_t address, uint8_t data);
};

#endif /* Memory_hpp */
