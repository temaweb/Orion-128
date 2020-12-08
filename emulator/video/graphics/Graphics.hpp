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

#ifndef Graphics_hpp
#define Graphics_hpp

#include "GraphicsContext.hpp"
#include "Video.hpp"

class Graphics
{
private:
    std::shared_ptr<Video> video;
    std::unique_ptr<GraphicsContext> context;
    
    static const short pixelVertices;
    
public:
    Graphics(std::shared_ptr<Video> video);
    
    void initialize();
    void render (double width, double height);
    
    bool isChanged() const;
private:
    
    void renderPixels (float width, float height);
    void renderPixels (float width, float height, int total);
    
    void drawColor (float * colors, Pixel pixel);
    void drawPixel (float * pixels, int col, int row, float width, float height);
    
    uint16_t getSize(int total, short vertices);
};

#endif /* Graphics_hpp */
