//
//  disk.hpp
//  orion
//
//  Created by Артём Оконечников on 17.11.2020.
//

#ifndef disk_hpp
#define disk_hpp

#include <stdio.h>
#include "IODevice.hpp"

class Disk : public IODevice
{
private:
    
    uint16_t address = 0x0000;
    std::array<uint16_t, 64 * 1024> rom;
    
public:
    Disk();
    
    virtual bool isPort(uint16_t address) override;
    virtual uint8_t read(const uint16_t address) const override;
    virtual void write(const uint16_t address, uint8_t data) override;
    
    void connect(std::shared_ptr<Bus> bus) override;
};

#endif /* disk_hpp */
