//
//  Bus.hpp
//  orion
//
//  Created by Артём Оконечников on 24.10.2020.
//

#ifndef Bus_hpp
#define Bus_hpp

#include <memory>
#include <map>

#include "IO.hpp"
#include "IODevice.hpp"
#include "MonitorRom.hpp"
#include "RamtestRom.hpp"
#include "System.hpp"

class Bus : public IODevice, public IO
{
private:
    
    std::shared_ptr<RDevice>   monitor = std::make_shared<MonitorRom>();
    std::shared_ptr<IODevice>  system  = std::make_shared<System>();
    
    std::map<Space, std::shared_ptr<RDevice>> rvector
    {
        { { 0xF800, 0xFFFF }, monitor },
        { { 0xF000, 0xF7FF }, system  }
    };
    
    std::map<Space, std::shared_ptr<WDevice>> wvector
    {
        { { 0xF000, 0xF7FF }, system  }
    };
    
public:
    
    void connect (std::shared_ptr<IODevice> memory);
    
public:
    
    virtual uint8_t read(const uint16_t address) const override;
    virtual void write(const uint16_t address, uint8_t data) override;
};

#endif /* Bus_hpp */
