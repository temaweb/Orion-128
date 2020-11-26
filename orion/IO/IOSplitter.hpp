//
//  IOSplitter.hpp
//  orion
//
//  Created by Артём Оконечников on 25.11.2020.
//

#ifndef IOSplitter_hpp
#define IOSplitter_hpp

#include <stdio.h>

#include "IO.hpp"
#include "IOController.hpp"

class IOSplitter : public IO<uint8_t>
{
private:
    std::shared_ptr<IOController> controller;
    
public:
    IOSplitter(std::shared_ptr<IOController> controller) : controller(controller)
    { }
    
    virtual uint8_t read(uint8_t device) const override
    {
        return controller -> read((device & 0xFF) << 8 | (device & 0xFF));
    }
    
    virtual void write(uint8_t device, uint8_t data) override
    {
        controller -> write((device & 0xFF) << 8 | (device & 0xFF), data);
    }
};

#endif /* IOSplitter_hpp */
