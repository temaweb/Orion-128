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
    uint8_t op = 0b11111111;
    uint16_t code = (uint16_t) (op & 0x38);
    
    std::cout << std::bitset<16>((uint16_t) (op & 0x38)) << std::endl;
    
    return 0;
}
