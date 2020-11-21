//
//  Switcher.cpp
//  orion
//
//  Created by Артём Оконечников on 20.11.2020.
//

#include "Switcher.hpp"

void Switcher::connect (std::shared_ptr<Video>  video)
{
    auto palette = std::make_shared<PaletteSwitch>(video);
    auto screen  = std::make_shared<ScreenSwitch>(video);

    insert(0xF800, palette);
    insert(0xFA00, screen);
}

void Switcher::connect (std::shared_ptr<Memory> memory)
{
    auto memswitch = std::make_shared<MemorySwitch>(memory);
    
    insert(0xF900, memswitch);
}

void Switcher::insert (uint16_t address, std::shared_ptr<WDevice> device)
{
    devices.insert(
       std::pair<uint16_t,
       std::shared_ptr<WDevice>>(address, device)
   );
}

#pragma mark -
#pragma mark I/O

bool Switcher::isAccept(uint16_t address) const
{
    return address >= 0xF800 &&
           address <= 0xFAFF;
}

void Switcher::write(const uint16_t address, uint8_t data)
{
    devices.at(address & 0xFF00) -> write(address, data);
}
