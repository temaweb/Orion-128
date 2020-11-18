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
#include <memory>
#include <cstdint>

#include "IODevice.hpp"
#include "IOBus.hpp"

class IOController : public IOBus
{
private:
    
    static const uint16_t begin = 0xF400;
    static const uint16_t end   = 0xFBFF;

    std::shared_ptr<IODevice> bus = nullptr;
    
protected:
    
    virtual std::shared_ptr<IODevice> defaultDevice() const override final;
    
public:
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override;
    void connectBus (std::shared_ptr<IODevice> bus);
};

#endif /* IOController_hpp */
