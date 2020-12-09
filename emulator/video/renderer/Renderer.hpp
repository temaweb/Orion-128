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

#ifndef Colorizer_hpp
#define Colorizer_hpp

#include <memory>
#include <array>

#include "Ram.hpp"
#include "Buffer.hpp"
#include "Pixel.hpp"
#include "Palette.hpp"

class Renderer
{
public:
    
    static const int width  = 384; // H points
    static const int height = 256; // V points
    
    typedef std::array<Pixel, width> frameline;
    typedef std::array<frameline, height> frame;
    
private:
    
    // Return 256 pixel frame line
    frameline getLine(Buffer * buffer, uint8_t row) const;
    
    // Colorize 8 pixels
    void colorise (frameline::iterator & line, uint8_t data, std::shared_ptr<Palette> palette) const;
    
public:
    
    virtual ~Renderer() = default;
    
    // Return one frame with resolution 384 x 256 pixels
    frame renderFrame(Buffer * buffer) const;
    
protected:
    Buffer buffer;
    virtual std::shared_ptr<Palette> getPalette(Buffer * buffer, uint16_t address) const = 0;
};

#endif /* Colorizer_hpp */
