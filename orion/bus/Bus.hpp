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
#include <vector>

//#include "IODevice.hpp"

class IODevice;

class Bus
{
private:
    std::array<uint8_t, 64 * 1024> ram;
    std::vector<std::shared_ptr<IODevice>> iodevices;
    
public:
    Bus();
    
    uint8_t read(const uint16_t address) const;
    void write(const uint16_t address, uint8_t data);
    
    void connect(std::shared_ptr<IODevice> device);
};

#endif /* Bus_hpp */
