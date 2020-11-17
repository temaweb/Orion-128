//
//  IODevice.hpp
//  orion
//
//  Created by Артём Оконечников on 16.11.2020.
//

#ifndef IODevice_hpp
#define IODevice_hpp

#include <stdio.h>
#include <cstdint>
#include <tuple>

#include "Bus.hpp"

class IODevice : public std::enable_shared_from_this<IODevice>
{
public:
    virtual bool isPort(uint16_t address) = 0;
    
    virtual uint8_t read(const uint16_t address) const = 0;
    virtual void write(const uint16_t address, uint8_t data) = 0;
    
    // Register in bus as I/O device
    virtual void connect(std::shared_ptr<Bus> bus)
    {
        bus -> connect(shared_from_this());
    }
};

#endif /* IODevice_hpp */
