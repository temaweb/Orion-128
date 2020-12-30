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

#include "Color16Palette.hpp"

Color16Palette::Color16Palette(uint8_t color) : color(color)
{ }

Pixel Color16Palette::getBackground() const
{
    return getPixel((color & 0xF0) >> 4);
}

Pixel Color16Palette::getForeground() const
{
    return getPixel(color & 0x0F);
}

Pixel Color16Palette::getPixel(uint8_t code) const
{
    auto color = palette[code];
    return Pixel(color);
}
