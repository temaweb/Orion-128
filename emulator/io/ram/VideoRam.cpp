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

#include "VideoRam.hpp"

VideoRam::VideoRam (
   pagetype::const_iterator frame,
   pagetype::const_iterator color) : frame(frame), color(color)
{
    setScreenMode(defaultScreen);
}

void VideoRam::setScreenMode (uint8_t mode)
{
    screen = spaces[mode];
}

void VideoRam::read (VideoBuffer & buffer) const
{
    copy (frame, buffer.getPixelsIterator());
    copy (color, buffer.getColorsIterator());
}

void VideoRam::copy (pagetype::const_iterator page, vbuffer::iterator buffer) const
{
    auto from = std::next(page, screen.from);
    auto to   = std::next(page, screen.to);

    std::copy (from, to, buffer);
}
