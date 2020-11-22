//
//  Video.cpp
//  orion
//
//  Created by Артём Оконечников on 11.11.2020.
//

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Video.hpp"
#include "Memory.hpp"

const BWPalette Video::bwpalette = BWPalette();

void Video::connect(std::shared_ptr<const Memory> memory)
{
    this -> memory = memory;
}

void Video::switchColorMode(uint8_t data)
{
    this -> colorMode = (ColorMode) (data >> 1);
}

// Returns one frame
std::array<std::array<Pixel, Video::width>, Video::height> Video::output()
{
    uint8_t row = 0x00;
    std::array<std::array<Pixel, width>, height> frame;

    do
    {
        std::array<Pixel, width> line = getLine(row);
        frame[row] = line;
    }
    while (row++ != height - 1);
    return frame;
}

// Returns one line
std::array<Pixel, Video::width> Video::getLine(uint8_t row)
{   
    std::array<Pixel, width> line;

    for (uint8_t col = 0x00; col < (width / 8); col++)
    {
        // Each video address in Orion has store column
        // index in high order bits and row index in low
        uint16_t address = begin + ((col << 8) | row);
        
        // One byte video data has 8 points on screen
        // Each set bit match drawed point on screen.
        uint8_t data = memory -> read(address);
        
        switch (colorMode)
        {
            case MONO:
            case COLOR4:
                colorisebw(line, col, data);
                break;
            case COLOR16:
                colorise16(line, col, data, address);
            default:
                break;
        }
    }
    
    return line;
}

void Video::colorise (std::array<Pixel, width> & line, size_t size, const uint8_t & data, const Palette & palette)
{
    for (uint8_t offset = 7;;offset--)
    {
        // Black pixel by default if no data
        Pixel pixel = palette.getBackground();
        
        if ((data & (1 << offset)))
        {
            // White pixel if bit is set
            pixel = palette.getForeground();
        }
        
        line[(size * 8) + (7 - offset)] = pixel;
        
        if (offset == 0x00)
            break;
    }
}

void Video::colorisebw(std::array<Pixel, width> & line, size_t size, const uint8_t & data)
{
    colorise(line, size, data, bwpalette);
}

void Video::colorise16(std::array<Pixel, width> & line, size_t size, const uint8_t & data, const uint16_t & address)
{
    // Read data by address from second page
    // Second page store data about colors;
    auto color = memory -> read(address, 1);
    auto palette = Color16Palette(color);
    
    colorise(line, size, data, palette);
}
