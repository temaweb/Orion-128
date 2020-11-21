//
//  IOController.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include "IOController.hpp"
#include "Disk.hpp"

IOController::IOController()
{
    auto disk = std::make_shared<Disk>();
    
    rdevices.push_back(disk);
    wdevices.push_back(disk);
}

std::shared_ptr<IODevice> IOController::defaultDevice() const
{
    return this -> bus;
}

#pragma mark -
#pragma mark Connect

void IOController::connect (std::shared_ptr<Device> device)
{   
    if (auto rdevice = std::dynamic_pointer_cast<RDevice>(device)) {
        rdevices.push_back(rdevice);
    }
    
    if (auto wdevice = std::dynamic_pointer_cast<WDevice>(device)) {
        wdevices.push_back(wdevice);
    }
}

void IOController::connect (std::shared_ptr<Bus> bus)
{
    this -> bus = bus;
}

#pragma mark -
#pragma mark I/O

bool IOController::isAccept(uint16_t address) const
{
    return address >= begin &&
           address <= end;
}

uint8_t IOController::read (const uint16_t address) const
{
    return getDevice<RDevice>(address, rdevices) -> read(address);
}

void IOController::write (const uint16_t address, uint8_t data)
{
    getDevice<WDevice>(address, wdevices) -> write(address, data);
}

