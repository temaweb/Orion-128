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

void Video::connect(std::shared_ptr<const Memory> bus)
{
    this -> bus = bus;
}

void Video::setPalette(uint8_t data)
{
    this -> palette = (Palette) (data >> 1);
}

std::vector<std::vector<Pixel>> Video::output()
{
    uint8_t row = 0x00;
    std::vector<std::vector<Pixel>> frame;

    do
    {
        std::vector<Pixel> line = getLine(row);
        frame.push_back(line);
    }
    while (row++ != height - 1);
    return frame;
}

std::vector<Pixel> Video::getLine(uint8_t row)
{
    std::vector<Pixel> line;
    
    for (uint8_t col = 0x00; col < (width / 8); col++)
    {
        // Each video address in Orion has store column
        // index in high order bits and row index in low
        uint16_t address = begin + ((col << 8) | row);
        
        // One byte video data has 8 points on screen
        // Each set bit match drawed point on screen.
        uint8_t  data = bus -> read(address);
        
       
        switch (palette)
        {
            case MONO:
                colorisebw(line, data);
                break;
            case COLOR4:
            case COLOR16:
                colorise16(line, data, address);
            default:
                break;
        }
    }
    
    return line;
}

void Video::colorisebw(std::vector<Pixel> & line, const uint8_t & data)
{
    for (uint8_t offset = 7;;offset--)
    {
        // Black pixel by default if no data
        Pixel pixel(0x000000);
        
        if ((data & (1 << offset)))
        {
            // White pixel if bit is set
            pixel = Pixel(0xCCCCCC);
        }
        
        line.push_back(pixel);
        
        if (offset == 0x00)
            break;
    }
}

void Video::colorise16(std::vector<Pixel> & line, const uint8_t & data, const uint16_t & address)
{
    uint8_t color = bus -> read(address, 1);
    
    uint32_t foreground = color16[color & 0x0F];
    uint32_t background = color16[(color & 0xF0) >> 4];
    
    for (uint8_t offset = 7;;offset--)
    {
        Pixel pixel(background);
        
        if ((data & (1 << offset)))
        {
            pixel = Pixel(foreground);
        }
        
        line.push_back(pixel);
        
        if (offset == 0x00)
            break;
    }
}
