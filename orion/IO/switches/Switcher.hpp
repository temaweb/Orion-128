//
//  Switcher.hpp
//  orion
//
//  Created by Артём Оконечников on 20.11.2020.
//

#ifndef Switcher_hpp
#define Switcher_hpp

#include <stdio.h>
#include <map>

#include "MemorySwitch.hpp"
#include "PaletteSwitch.hpp"
#include "ScreenSwitch.hpp"

class Switcher : public WDevice
{
private:
      std::map<uint16_t, std::shared_ptr<WDevice>> devices;
    
public:

    void connect (std::shared_ptr<Video>  video);
    void connect (std::shared_ptr<Memory> memory);
    
    void insert (uint16_t address, std::shared_ptr<WDevice> device);
public:
    
    virtual bool isAccept(uint16_t address) const override;
    virtual void write(const uint16_t address, uint8_t data) override;
};

#endif /* Switcher_hpp */
