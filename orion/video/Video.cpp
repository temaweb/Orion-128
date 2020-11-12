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
#include "Bus.hpp"

void Video::connect(Bus * bus)
{
    _bus = bus;
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
        uint8_t  data = _bus -> read(address);
        
        explore(line, data);
    }
    
    return line;
}

void Video::explore(std::vector<Pixel> & line, uint8_t data)
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
