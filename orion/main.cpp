//
//  main.cpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#include <iostream>
#include <cstdint>

#include "i8080.hpp"

void read(uint8_t s)
{
    std::cout << +s << std::endl;
}

int main(int argc, const char * argv[])
{
//    uint8_t data = 0b10101010;
//    std::bitset<8> revert(data ^ 0xFF);
//
//    std::cout << (0 << 1) << std::endl;
//    std::cout << (1 << 1) << std::endl;
//    std::cout << (2 << 1) << std::endl;
//    std::cout << (3 << 1) << std::endl;
//
    
    uint8_t s = 0x00;
    
    read(s++);
    read(s++);
    read(s);
    return 0;
}
