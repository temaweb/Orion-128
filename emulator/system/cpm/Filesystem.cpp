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

#include "Filesystem.hpp"
#include "Environment.hpp"

Filesystem::Filesystem(std::shared_ptr<Memory> memory) : memory(memory)
{}

int Filesystem::getLength(std::vector<uint8_t>::const_iterator & begin, std::vector<uint8_t>::size_type size)
{
    int length = (begin[0x0B] << 8) | begin[0x0A];
    if (length == 0)
    {
        const int offset = 0x4D;

        if (size < offset + 32) {
            return 0;
        }

        begin = std::next(begin, offset);
        length = (begin[0x0B] << 8) | begin[0x0A];
    }

    return (((length - 1) | 0xF ) + 17);
}

void Filesystem::create(std::string path)
{
    std::vector<uint8_t> content;
    Environment::readBinaryFile(path, content);
    
    auto begin = content.cbegin();
    auto size  = content.size();

    auto length = getLength(begin, size);
    
    for (uint16_t i = 0; i < length; i++)
    {
        memory -> writeB(i, *begin++);
    }
    
    // Add end byte
    memory -> writeB(length, 0xFF);
}
