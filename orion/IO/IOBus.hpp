//
//  IOBus.h
//  orion
//
//  Created by Артём Оконечников on 18.11.2020.
//

#ifndef IOBus_h
#define IOBus_h

#include <vector>
#include "IODevice.hpp"

class IOBus : public IODevice
{
private:
    std::vector<std::shared_ptr<Device>> devices;
    
    template<class T>
    std::shared_ptr<T> getDeviceOrDefault(uint16_t address) const
    {
        for (auto & device : devices)
        {
            if (device -> isAccept(address))
            {
                auto object = std::dynamic_pointer_cast<T>(device);
                if (object)
                    return object;
            }
        }
        
        return defaultDevice();
    }
    
protected:
    
    template<class T>
    std::shared_ptr<T> getDevice(uint16_t address) const
    {
        if (isAccept(address)) {
            return getDeviceOrDefault<T>(address);
        }
        
        return defaultDevice();
    }
    
    virtual std::shared_ptr<IODevice> defaultDevice() const = 0;
    
public:
    
    // I/O
    virtual uint8_t read (const uint16_t address) const override;
    virtual void   write (const uint16_t address, uint8_t data) override;
    
    void connect (std::shared_ptr<Device> device);
    
    template<class T>
    void connect ()
    {
        connect(std::make_shared<T>());
    }
};

#endif /* IOBus_h */
