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

#ifndef Video_hpp
#define Video_hpp

#include <array>
#include <cstdint>
#include <shared_mutex>

#include "VideoRam.hpp"
#include "Colorizer.hpp"

struct Resolution
{
    const int width;
    const int height;
};

class Video
{
private:
    enum ColorMode
    {
        MONO    = 0,  // B/W color
        BLANK   = 1,  // No image
        COLOR4  = 2,  // 4 color palette
        COLOR16 = 3   // 16 color palettex
    };
    
    std::unique_ptr<Colorizer> colorizer;
    std::shared_mutex mutex;
    
private:
    std::shared_ptr<const VideoRam> vram;
    std::shared_ptr<VideoBuffer> buffer;
    
public:
    Video(std::shared_ptr<const VideoRam> vram);
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has color in RGB hex-format.
    Colorizer::frame output();

    void refreshBuffer ();
    void setColorMode  (uint8_t mode);
    
    bool isChanged() const;
    
    // Return video resolution
    Resolution getResolution() const
    {
        return
        {
            Colorizer::width,
            Colorizer::height
        };
    }
};

#endif /* Video_hpp */
