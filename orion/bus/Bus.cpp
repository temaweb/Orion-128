//
//  Bus.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <sstream>
#include <tuple>

#include "Bus.hpp"
#include "IODevice.hpp"

Bus::Bus()
{
    for (auto &a : ram)
    {
        a = 0x00;
    }
}

uint8_t Bus::read(const uint16_t address) const
{
    for (auto & device : iodevices)
    {
        if (device -> isPort(address)) {
            return device -> read(address);
        }
    }
    
    if (address >= 0x00 && address <= 0xFFFF)
        return ram[address];
    
    return 0x00;
}

void Bus::write(const uint16_t offset, uint8_t data)
{
    for (auto & device : iodevices)
    {
        if (device -> isPort(offset)) {
            device -> write(offset, data);
            return;
        }
    }
    
    if (offset >= 0x00 && offset <= 0xFFFF)
        ram[offset] = data;
}

void Bus::connect(std::shared_ptr<IODevice> device)
{
    iodevices.push_back(device);
}
