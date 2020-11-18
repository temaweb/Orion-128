//
//  Bus.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <stdexcept>

#include "Bus.hpp"
#include "IODevice.hpp"

std::shared_ptr<IODevice> Bus::getDevice(uint16_t address) const
{
    for (auto & device : devices)
    {
        if (device -> isAccept(address))
            return device;
    }
    
    throw std::out_of_range("No device found for address");
}

uint8_t Bus::read(const uint16_t address) const
{
    return getDevice(address) -> read(address);
}

void Bus::write(const uint16_t address, uint8_t data)
{
    getDevice(address) -> write(address, data);
}
