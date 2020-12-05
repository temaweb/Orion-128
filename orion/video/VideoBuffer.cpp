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

#include "VideoBuffer.hpp"

VideoBuffer::VideoBuffer(std::shared_ptr<const VideoRam> vram) : vram(vram)
{ }

void VideoBuffer::refreshBuffer()
{
    vram -> readPixel(videoBuffer.getPixel());
    vram -> readColor(videoBuffer.getColor());
}

void VideoBuffer::exchangeBuffer()
{
    frameBuffer = videoBuffer;
}

bool VideoBuffer::isChanged()
{
    return frameBuffer != videoBuffer;
}

uint8_t VideoBuffer::readFrameBuffer(uint16_t address) const
{
    return frameBuffer.pixels[address];
}

uint8_t VideoBuffer::readColorBuffer(uint16_t address) const
{
    return frameBuffer.colors[address];
}
