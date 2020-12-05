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

#include "Buffer.hpp"

vbuffer::iterator Buffer::getPixel()
{
    return pixels.begin();
}

vbuffer::iterator Buffer::getColor()
{
    return colors.begin();
}

bool Buffer::operator==(const Buffer & buffer) const
{
    if (pixels != buffer.pixels)
        return false;

    return colors == buffer.colors;
}

bool Buffer::operator!=(const Buffer & buffer) const
{
    return !(*this == buffer);
}

uint8_t Buffer::readFrame(uint16_t address) const
{
    return pixels[address];
}

uint8_t Buffer::readColor(uint16_t address) const
{
    return colors[address];
}
