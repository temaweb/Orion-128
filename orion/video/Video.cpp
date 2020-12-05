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

#include "Video.hpp"

#include "Color16Colorizer.hpp"
#include "BWColorizer.hpp"

Video::Video(std::shared_ptr<const VideoRam> vram) : vram(vram)
{
    buffer = std::make_shared<VideoBuffer>(vram);
    setColorMode(0x00);
}

void Video::setColorMode (uint8_t mode)
{
    switch ((ColorMode) (mode >> 1))
    {
        case COLOR16:
            colorizer = std::make_unique<Color16Colorizer>(buffer);
            break;
        default:
            colorizer = std::make_unique<BWColorizer>(buffer);
    }
}

bool Video::isChanged() const
{
    return buffer -> isChanged();
}

void Video::refreshBuffer ()
{
    std::unique_lock lock(mutex);
    buffer -> refreshBuffer();
}

Colorizer::frame Video::output()
{
    std::shared_lock lock(mutex);
    buffer -> exchangeBuffer();
    
    return colorizer -> getFrame();
}
