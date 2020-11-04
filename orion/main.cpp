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
    uint8_t data = 0b10101010;
    std::bitset<8> revert(data ^ 0xFF);
    
    uint8_t x = 1;
    uint8_t y = 5;
    
    std::cout << !x << std::endl;
    
    return 0;
}
