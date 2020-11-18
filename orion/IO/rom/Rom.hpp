//
//  Rom.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef Rom_hpp
#define Rom_hpp

#include <stdio.h>
#include <fstream>
#include <array>

#include "IODevice.hpp"

template<size_t size = 2 * 1024>
class Rom : public IODevice
{
private:

    static const uint16_t begin = 0xF800;
    static const uint16_t end   = 0xFFFF;
    
    std::ifstream open(std::string path)
    {
        return std::ifstream(path, std::ios::in | std::ios::binary);
    }
    
protected:
    
    std::array<uint8_t, size> rom;
    
public:
    
    // Load ROM file from disk
    Rom(std::string path)
    {
        auto file = open(path);
        char buffer = 0x00;
        
        for (auto & byte : rom)
        {
            if (file.eof())
            {
                byte = 0x00;
            }
            else
            {
                file.read(&buffer, sizeof(buffer));
                byte = buffer;
            }
        }

        file.close();
    }
    
    // Address belong to ports space
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= begin &&
               address <= end;
    }
    
    #pragma mark -
    #pragma mark I/O
    
    // I/O
    virtual uint8_t read (const uint16_t address) const override
    {
        return rom[address - begin];
    }
    
    virtual void write (const uint16_t address, uint8_t data) override
    {
        rom[address - begin] = data;
    }
};

#endif /* Rom_hpp */
