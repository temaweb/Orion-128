//
//  EmptyDevice.h
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef EmptyDevice_h
#define EmptyDevice_h

#include <iostream>
#include <iomanip>

#include "IODevice.hpp"

class Empty : public IODevice
{
private:
    static std::shared_ptr<IODevice> instance;
    
public:

    static std::shared_ptr<IODevice> getInstance();
    
    virtual uint8_t read (const uint16_t address) const override;
    virtual void write (const uint16_t address, uint8_t data) override;
};

#endif /* EmptyDevice_h */
