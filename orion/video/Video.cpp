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

#include "Color16Renderer.hpp"
#include "GenericRenderer.hpp"

#include "BWPalette.hpp"
#include "BlankPalette.hpp"

const std::array<std::shared_ptr<const Renderer>, 4> Video::renders
{
    // B/W color
    std::make_shared<GenericRenderer<BWPalette>>(),
    
    // No image
    std::make_shared<GenericRenderer<BlankPalette>>(),
    
    // 4 color palette (not supported)
    std::make_shared<GenericRenderer<BWPalette>>(),
    
    // 16 color palette
    std::make_shared<Color16Renderer>()
};

Video::Video(std::shared_ptr<const VideoRam> vram) : vram(vram)
{
    // Set B/W as default
    setColorMode(0x00);
}

void Video::setColorMode (uint8_t mode)
{
    renderer = renders[(mode >> 1)];
}

bool Video::isChanged() const
{
    return frameBuffer != videoBuffer;
}

void Video::swapBuffer ()
{
    std::unique_lock lock(mutex);
    frameBuffer = videoBuffer;
}

void Video::refresh ()
{
    std::unique_lock lock(mutex);
    vram -> read(videoBuffer);
}

Renderer::frame Video::output()
{
    swapBuffer();
    return renderer -> renderFrame(&frameBuffer);
}
