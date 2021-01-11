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

#ifndef Filesystem_hpp
#define Filesystem_hpp

#include <vector>
#include "Memory.hpp"

class Filesystem
{
private:
    std::shared_ptr<Memory> memory;

    int getLength(
          std::vector<uint8_t>::const_iterator & iterator,
          std::vector<uint8_t>::size_type size);
    
public:
    Filesystem(std::shared_ptr<Memory> memory);
    void create (std::string path);
};

#endif /* Filesystem_hpp */
