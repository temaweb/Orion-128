//
//  main.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <iostream>
#include <cstdint>

#include "i8080.hpp"

int main(int argc, const char * argv[])
{
    uint8_t data = 0b11000100;
    
    // (bool)(data & 0x80)
    // data | 0x01
    
    std::cout << std::bitset<8>(~data) << std::endl;
    
    return 0;
}
