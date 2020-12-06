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

#include <limits>

#include "Graphics.hpp"
#include "Renderer.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

const short Graphics::pixelVertices = 12;

Graphics::Graphics(std::shared_ptr<Video> video) : video(video)
{
    context = std::make_unique<GraphicsContext>();
}

void Graphics::initialize()
{
    context -> initialize();
}

void Graphics::render(double width, double height)
{
    context -> initializeLayout(width, height);
    renderPixels(width, height);
}

void Graphics::renderPixels (float width, float height)
{
    // Pixel screen dimensions
    float pixelHeight = (height - Renderer::height) / Renderer::height;
    float pixelWidth  = (width  - Renderer::width)  / Renderer::width;
    
    // Total pixels
    int total = Renderer::height * Renderer::width;
    
    renderPixels(pixelWidth, pixelHeight, total);
}

void Graphics::renderPixels(float width, float height, int total)
{
    // Vertex buffers
    float * pixels = nullptr;
    float * colors = nullptr;
    
    // Current vertex buffer index
    int index = 0;
    
    // Buffer size
    uint16_t size  = 0x0000;
    
    // Frame
    auto output = video -> output();
    
    int row = 0;
    for (auto line = output.rbegin(); line != output.rend(); line++)
    {
        int col = 0;
        for (auto & pixel : *line)
        {
            int shape = index * pixelVertices;
            if (shape == size)
            {
                size = getSize(total, pixelVertices);
                
                pixels = new float[size];
                colors = new float[size];
                
                index = 0;
                shape = 0;
            }

            drawColor(&colors[shape], pixel);
            drawPixel(&pixels[shape], col, row, width, height);
            
            if (--total == 0 || ((index + 1) * pixelVertices) == size)
            {
                context -> flushBuffers(pixels, colors, size);
                
                delete[] pixels;
                delete[] colors;
            }
            
            index++;
            col++;
        }

        row++;
    }
    
    context -> flush();
}

void Graphics::drawColor (float * colors, Pixel pixel)
{
    float r = pixel.getRed();
    float g = pixel.getGreen();
    float b = pixel.getBlue();
    
    for (int i = 0; i < 4; i++)
    {
        *(colors++) = r;
        *(colors++) = g;
        *(colors++) = b;
    }
}

void Graphics::drawPixel (float * pixels, int col, int row, float width, float height)
{
    float x = (col * width)  + col;
    float y = (row * height) + row;
    float z = 0.0f;

    float dimensions[2][4] =
    {
        { height, height, 0.0f,  0.0f },
        { 0.0f,   width,  width, 0.0f }
    };
    
    for (int i = 0; i < 4; i++)
    {
        *(pixels++) = x + dimensions[0][i];
        *(pixels++) = y + dimensions[1][i];
        *(pixels++) = z;
    }
}

uint16_t Graphics::getSize(int total, short vertices)
{
    int max = (USHRT_MAX - (USHRT_MAX % vertices));
    
    if (total >= (max / vertices))
        return max;
    
    return total * vertices;
}

#pragma clang diagnostic pop
