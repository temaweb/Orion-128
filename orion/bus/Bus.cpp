//
//  Bus.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <sstream>
#include "Bus.hpp"

Bus::Bus()
{
    for (auto &a : ram)
    {
        a = 0x00;
    }
}

uint8_t Bus::read(const uint16_t offset) const
{
    if (offset >= 0x00 && offset <= 0xFFFF)
        return ram[offset];
    
    return 0x00;
}

void Bus::write(const uint16_t offset, uint8_t data)
{
    if (offset >= 0x00 && offset <= 0xFFFF)
        ram[offset] = data;
}

//uint64_t toHex(std::string token)
//{
//    uint64_t value  = 0x0000;
//    std::istringstream buffer(token);
//    buffer >> std::hex >> value;
//
//    return value;
//}
//
//void Bus::write(std::string data)
//{
//    uint16_t offset = 0x0000;
//
//    size_t pos = 0;
//    std::string token;
//
//    while ((pos = data.find(' ')) != std::string::npos)
//    {
//        token = data.substr(0, pos);
//        this -> write(offset++, toHex(data));
//        data.erase(0, pos + 1);
//    }
//
//    this -> write(offset, toHex(data));
//}
