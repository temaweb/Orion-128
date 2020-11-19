//
//  disk.hpp
//  orion
//
//  Created by Артём Оконечников on 17.11.2020.
//

#ifndef disk_hpp
#define disk_hpp

#include <stdio.h>
#include <array>

#include "IODevice.hpp"
#include "Rom.hpp"

class Disk : public WDevice, public Rom<64 * 1024>
{
private:
    
    uint16_t address = 0x0000;
    
    enum
    {
        LO = 0x01,
        HI = 0x02
    };
    
public:
    Disk() : Rom("rom/Orion128_RomDisk4.rom")
    {}
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= 0xF500 &&
               address <= 0xF5FF;
    }
    
    // I/O
    virtual uint8_t read(const uint16_t address) const override
    {
        return rom[this -> address];
    }
    
    virtual void write(const uint16_t address, uint8_t data) override
    {
        int flag = address & 0x03;
        
        if (flag == LO) {
            this -> address = (this -> address & 0xFF00) | data;
        }
        
        if (flag == HI) {
            this -> address = (this -> address & 0x00FF) | (data << 8);
        }
    }
};

#endif /* disk_hpp */
