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
    uint16_t data = 0b11001001;
    
    
    if ((data & 0x000F) > 0x0009)
    {
        data |= 0x0006;
    }

    if (((data & 0x00F0) >> 4) > 0x0009)
    {
        data |= 0x0060;
    }
    
    std::cout << std::bitset<16>(data | 0x0060) << std::endl;
    
    return 0;
}
