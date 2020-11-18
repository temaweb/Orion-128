//
//  EmptyDevice.cpp
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#include <stdio.h>

#include "Empty.hpp"

std::shared_ptr<IODevice> Empty::instance = nullptr;

std::shared_ptr<IODevice> Empty::getInstance()
{
    if (instance == nullptr)
        instance = std::make_shared<Empty>();

    return instance;
}

uint8_t Empty::read (const uint16_t address) const
{
    return 0x00;
}

void Empty::write (const uint16_t address, uint8_t data)
{
    using namespace std;
    
    cout << uppercase;
    
    cout << "W:"
        << setfill(' ') << " 0x" << setw(4) << setfill('0') << hex << address
        << setfill(' ') << " 0x" << setw(2) << setfill('0') << hex << unsigned(data);
    
    cout << endl;
}
