//
//  VideoMemory.hpp
//  orion
//
//  Created by Артём Оконечников on 23.11.2020.
//

#ifndef VideoMemory_hpp
#define VideoMemory_hpp

#include <stdio.h>

#include "Video.hpp"
#include "IODevice.hpp"

class VideoObserver : public IODevice
{
private:
    
    static const uint16_t begin = 0x0C000;
    static const uint16_t end   = 0x0EFFF;
    
    std::shared_ptr<Video> video;
    std::shared_ptr<IODevice> memory;
    
public:
    
    VideoObserver(std::shared_ptr<IODevice> memory, std::shared_ptr<Video> video)
        : video(video), memory(memory)
    { }
    
    virtual bool isAccept(uint16_t address) const override
    {
        return address >= begin &&
               address <= end;
    }
    
    virtual uint8_t read(const uint16_t address) const override
    {
        return memory -> read(address);
    }
    
    virtual void write(const uint16_t address, uint8_t data) override
    {
        if (read(address) != data)
        {
            video  -> markChanged();
            memory -> write(address, data);
        }
    }
};

#endif /* VideoMemory_hpp */
