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
#include <vector>

#include "IODevice.hpp"

class Bus
{
private:
    std::vector<std::shared_ptr<IODevice>> devices;
    std::shared_ptr<IODevice> getDevice(uint16_t address) const;
    
public:
    
    uint8_t read (const uint16_t address) const;
    void   write (const uint16_t address, uint8_t data);
    
    // Add I/O device
    void connect(std::shared_ptr<IODevice> device)
    {
        devices.push_back(device);
    }
};

#endif /* Bus_hpp */
