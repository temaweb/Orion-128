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
#include "Renderer.hpp"

class Video
{
private:
    static const std::array<std::shared_ptr<const Renderer>, 4> renders;
    
private:
    std::mutex mutex;
    
    std::shared_ptr<const VideoRam> vram;
    std::shared_ptr<const Renderer> renderer;
    
    Buffer videoBuffer;
    Buffer frameBuffer;
    
    // Set video buffer as current frame buffer
    void swapBuffer ();
    
public:
    Video(std::shared_ptr<const VideoRam> vram);
    
    // Return one frame with resolution 384 x 256 pixels
    // Each pixel has color in RGB hex-format.
    Renderer::frame output();

    // Update video buffer
    void refresh ();
    
    // Change color palette
    void setColorMode  (uint8_t mode);
    
    // Returns true if frame buffer differs from video buffer
    bool isChanged() const;
};

#endif /* Video_hpp */
