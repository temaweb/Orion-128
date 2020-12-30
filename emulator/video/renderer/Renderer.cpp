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

#include "Renderer.hpp"

Renderer::frame Renderer::renderFrame(VideoBuffer * buffer) const
{
    uint8_t row = 0x00;
    frame frame;

    do
    {
        frame[row] = getLine(buffer, row);
    }
    while (row++ != height - 1);
    return frame;
}

Renderer::frameline Renderer::getLine(VideoBuffer * buffer, uint8_t row) const
{
    frameline line;
    frameline::iterator lineit = line.begin();
    
    for (uint8_t col = 0x00; col < (width / 8); col++)
    {
        // Each video address in Orion has store column
        // index in high order bits and row index in low
        uint16_t address = ((col << 8) | row);
        
        // One byte video data has 8 points on screen
        // Each set bit match drawed point on screen.
        uint8_t data = buffer -> readFrame(address);

        // Get current palette
        // TODO: Bad design. Palette should be one of whole frame
        auto palette = getPalette(buffer, address);
        
        // Colorize pixel data by palettes
        colorise(lineit, data, palette);
    }
    
    return line;
}

void Renderer::colorise (frameline::iterator & line, uint8_t data, std::shared_ptr<Palette> palette) const
{
    for (uint8_t offset = 0x08; offset > 0x00;)
    {
        // Background pixel by default if no data
        Pixel pixel = palette -> getBackground();

        if (data & (1 << --offset))
        {
            // Foreground pixel if bit is set
            pixel = palette -> getForeground();
        }

        *(line++) = pixel;
    }
}
