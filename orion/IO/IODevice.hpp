//
//  IODevice.hpp
//  orion
//
//  Created by Артём Оконечников on 16.11.2020.
//

#ifndef IODevice_hpp
#define IODevice_hpp

#include <cstdint>

class IODevice
{
public:

    // Device should be proccess the address range
    virtual bool isAccept(uint16_t address) const = 0;
    
    virtual uint8_t read(const uint16_t address) const = 0;
    virtual void write(const uint16_t address, uint8_t data) = 0;
};

#endif /* IODevice_hpp */
