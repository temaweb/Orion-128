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
#include <memory>
#include <stdexcept>

#include "IOBus.hpp"
#include "IODevice.hpp"
#include "Empty.hpp"

class Bus : public IOBus
{
protected:
    
    virtual std::shared_ptr<IODevice> defaultDevice() const override final
    {
        return Empty::getInstance();
    }
};

#endif /* Bus_hpp */
