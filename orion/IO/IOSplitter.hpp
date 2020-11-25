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

class IOSplitter : public IO
{
private:
    std::shared_ptr<IOController> controller;
    
public:
    IOSplitter(std::shared_ptr<IOController> controller) : controller(controller)
    { }
    
    virtual uint8_t read(const uint16_t address) const override
    {
        return controller -> read((address & 0x00FF) << 8 | (address & 0x00FF));
    }
    
    virtual void write(const uint16_t address, uint8_t data) override
    {
        controller -> write((address & 0x00FF) << 8 | (address & 0x00FF), data);
    }
};

#endif /* IOSplitter_hpp */
