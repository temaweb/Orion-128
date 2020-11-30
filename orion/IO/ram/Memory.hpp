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

#include "IODevice.hpp"

class Memory : public IODevice
{
private:
    static const uint16_t video = 0xC000;
    
    uint8_t page = 0x00;
    std::array<std::array<uint8_t, 60 * 1024>, 4> memory {};
    
public:
    Memory();
    
    virtual Space getSpace() const override;
    
    uint8_t read (uint16_t address) const override;
    uint8_t read (uint16_t address, uint8_t page) const;
    
    void write (uint16_t address, uint8_t data) override;
    void write (uint16_t address, uint8_t data, uint8_t page);
    
    void switchPage(uint8_t page);
    
    std::array<uint8_t, 12 * 1024> getFrameBuffer() const;
    std::array<uint8_t, 12 * 1024> getColorBuffer() const;
    
    std::array<uint8_t, 12 * 1024> getVideoBuffer(uint8_t page) const;
};

#endif /* Memory_hpp */
