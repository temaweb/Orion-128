//
//  IOController.cpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#include "IOController.hpp"

// Address belong to ports space
bool IOController::isAccept(uint16_t address) const
{
    return address >= begin && address <= end;
}

std::shared_ptr<IODevice> IOController::defaultDevice() const
{
    return this -> bus;
}

void IOController::connectBus (std::shared_ptr<IODevice> bus)
{
    this -> bus = bus;
}


