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

#include "Pixel.hpp"

Pixel::Pixel() : Pixel(0x000000)
{ }

Pixel::Pixel(uint32_t color) : color(color)
{ }

Pixel::Pixel(const Pixel & pixel) : Pixel(pixel.color)
{ }

Pixel& Pixel::operator=(const Pixel & pixel)
{
    return *new(this) Pixel(pixel);
}

float Pixel::getRed() const
{
    return (float) ((color & 0xFF0000) >> 16) / 255.0;
}

float Pixel::getGreen() const
{
    return (float) ((color & 0x00FF00) >> 8) / 255.0;
}

float Pixel::getBlue() const
{
    return (float) (color & 0x0000FF) / 255.0;
}
