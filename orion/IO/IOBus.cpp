//
//  IOBus.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include <stdio.h>
#include "IOBus.hpp"

void IOBus::connect (std::shared_ptr<Device> device)
{
    devices.push_back(device);
}

// I/O
uint8_t IOBus::read (const uint16_t address) const
{
    return getDevice<RDevice>(address) -> read(address);
}

void IOBus::write (const uint16_t address, uint8_t data)
{
    getDevice<WDevice>(address) -> write(address, data);
}
