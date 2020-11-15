//
//  Rom.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include "Rom.hpp"

const std::string Rom::dir = "/Users/temaweb/Desktop/Орион-128/Orion-128/monitor/";

void Rom::load (std::shared_ptr<Bus> bus)
{
    auto offset = getOffset();
    auto file   = open();
    
    char buffer = 0x00;
    
    while (!file.eof())
    {
        file.read(&buffer, sizeof(buffer));
        bus -> write(offset++, buffer);
    }
    
    file.close();
}

std::ifstream Rom::open()
{
    auto file = getRom();
    auto path = dir + file;
    
    return std::ifstream(path, std::ios::in | std::ios::binary);
}
