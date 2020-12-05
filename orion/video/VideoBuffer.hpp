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

#ifndef VideoBuffer_hpp
#define VideoBuffer_hpp

#include "VideoRam.hpp"
#include "Buffer.hpp"

class VideoBuffer
{
private:
    Buffer videoBuffer {};
    Buffer frameBuffer {};
    
    std::shared_ptr<const VideoRam> vram;
    
public:
    VideoBuffer(std::shared_ptr<const VideoRam> vram);
    
    void refreshBuffer  ();
    void exchangeBuffer ();
    
    bool isChanged();
    
    uint8_t readFrameBuffer(uint16_t address) const;
    uint8_t readColorBuffer(uint16_t address) const;
};

#endif /* VideoBuffer_hpp */
