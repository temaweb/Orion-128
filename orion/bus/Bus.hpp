//
//  Bus.hpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#ifndef Bus_hpp
#define Bus_hpp

#include <stdio.h>
#include <cstdint>
#include <array>

class Bus
{
private:
    std::array<uint8_t, 128 * 1024> ram;
    
public:
    Bus();
    
    uint8_t read(uint16_t offset) const;
    void write(uint16_t offset, uint8_t data);
};

#endif /* Bus_hpp */
