//
//  IODevice.hpp
//  orion
//
//  Created by Артём Оконечников on 16.11.2020.
//

#ifndef IODevice_hpp
#define IODevice_hpp

#include <cstdint>

struct Space
{
    uint16_t from;
    uint16_t to;
    
    bool operator < (const Space & space) const
    {
        return from < space.from;
    }
    
    uint16_t getDirect(uint16_t address) const
    {
        return address - from;
    }
    
    bool inRange(uint16_t address) const
    {
        return !(address < from || address > to);
    }
};

class Device
{
public:

    // Device should be proccess the address range
    virtual bool isAccept(uint16_t address) const
    {
        return true;
    }
};

// Read-only devices
class RDevice : virtual public Device
{
public:

    virtual uint8_t read(const uint16_t address) const = 0;
};

// Write-only devices
class WDevice : virtual public Device
{
public:

    virtual void write(const uint16_t address, uint8_t data) = 0;
};

// R/W device
class IODevice : public RDevice, public WDevice
{

};

#endif /* IODevice_hpp */
