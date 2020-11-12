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
#include <string>
#include <array>

class Bus
{
private:
    std::array<uint8_t, 64 * 1024> ram;
    
public:
    Bus();
    
    virtual uint8_t read(const uint16_t address) const;
    virtual void write(const uint16_t address, uint8_t data);
    
    void write(std::string data);
};

#endif /* Bus_hpp */
