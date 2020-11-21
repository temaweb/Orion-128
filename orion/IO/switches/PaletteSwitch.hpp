//
//  ColorSwitcher.h
//  orion
//
//  Created by Артём Оконечников on 19.11.2020.
//

#ifndef ColorSwitcher_h
#define ColorSwitcher_h

#include "IODevice.hpp"
#include "Video.hpp"

class PaletteSwitch : public WDevice
{
private:
    std::shared_ptr<Video> video;
    
public:
    PaletteSwitch(std::shared_ptr<Video> video) : video(video)
    { }

    virtual void write (const uint16_t address, uint8_t data) override
    {
        video -> switchColorMode(data & 0x7);
    }
};

#endif /* ColorSwitcher_h */
