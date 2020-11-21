//
//  IOController.hpp
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef IOController_hpp
#define IOController_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
#include <typeinfo>
#include <typeindex>

#include "IODevice.hpp"
#include "Bus.hpp"

template <class T>
using devices = std::vector<std::shared_ptr<T>>;

class IOController : public IODevice
{
private:
    
    static const uint16_t begin = 0xF400;
    static const uint16_t end   = 0xFBFF;

    devices<RDevice> rdevices;
    devices<WDevice> wdevices;
    
    std::shared_ptr<IODevice> bus = nullptr;
    std::shared_ptr<IODevice> defaultDevice() const;
    
    template<class T>
    std::shared_ptr<T> getDevice(uint16_t address, const devices<T> & devices) const
    {
        if (isAccept(address))
        {
            for (auto & device : devices)
            {
                if (device -> isAccept(address))
                    return device;
            }
        }
        
        return defaultDevice();
    }
    
public:
    IOController();
    
    void connect (std::shared_ptr<Device> device);
    void connect (std::shared_ptr<Bus> bus);
    
public:
    
    virtual bool isAccept(uint16_t address) const override;
    virtual uint8_t read (const uint16_t address) const override;
    virtual void write (const uint16_t address, uint8_t data) override;
};

#endif /* IOController_hpp */
