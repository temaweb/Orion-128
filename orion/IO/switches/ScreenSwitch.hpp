//
//  DisplaySwitcher.h
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef DisplaySwitcher_h
#define DisplaySwitcher_h

#include "IODevice.hpp"
#include "Video.hpp"

class ScreenSwitch : public WDevice
{
private:
    std::shared_ptr<Video> video;
    
public:
    ScreenSwitch(std::shared_ptr<Video> video) : video(video)
    {}
    
    virtual void write (const uint16_t address, uint8_t data) override
    {
        // (~value & 0x3) << 14
    }
};

#endif /* DisplaySwitcher_h */
