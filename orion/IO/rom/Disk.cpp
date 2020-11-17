//
//  disk.cpp
//  orion
//
//  Created by Артём Оконечников on 17.11.2020.
//

#include <fstream>
#include "Disk.hpp"

Disk::Disk()
{
    for (auto &a : rom)
    {
        a = 0x00;
    }
}

void Disk::connect(std::shared_ptr<Bus> bus)
{
    IODevice::connect(bus);
    
    auto stream = std::ifstream("/Users/temaweb/Desktop/Орион-128/Orion-128/rom/romdisk2.bin", std::ios::in | std::ios::binary);
    char buffer = 0x00;
    uint16_t offset = 0x0000;
    
    while (!stream.eof())
    {
        stream.read(&buffer, sizeof(buffer));
        rom[offset++] = buffer;
    }
    
    stream.close();
}

#pragma mark -
#pragma mark IO

uint8_t Disk::read(const uint16_t address) const
{
    return rom[this -> address];
}

void Disk::write(const uint16_t address, uint8_t data)
{
    int offset = ((address - 0xF500) & 0x03);
    
    if (offset == 0x01) {
        this -> address = (this -> address & 0xFF00) | data;
    }
    
    if (offset == 0x02) {
        this -> address = (this -> address & 0x00FF) | (data << 8);
    }
}

bool Disk::isPort(uint16_t address)
{
    return address >= 0xF500 &&
           address <= 0xF5FF;
}
