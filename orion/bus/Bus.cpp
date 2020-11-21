//
//  Bus.cpp
//  orion
//
//  Created by Артём Оконечников on 20.11.2020.
//

#include "Bus.hpp"

template<class T>
using pair = std::pair<Space, std::shared_ptr<T>>;

void Bus::connect (std::shared_ptr<IODevice> memory)
{
    rvector.insert(pair<RDevice>({ 0x0000, 0xEFFF }, memory));
    wvector.insert(pair<WDevice>({ 0x0000, 0xEFFF }, memory));
}

uint8_t Bus::read(const uint16_t address) const
{
    for (auto const & [space, device] : rvector)
    {
        if (space.inRange(address))
        {
            auto direct = space.getDirect(address);
            return device -> read(direct);
        }
    }
    
    return 0x00;
}

void Bus::write(const uint16_t address, uint8_t data)
{
    for (auto const & [space, device] : wvector)
    {
        if (space.inRange(address))
        {
            auto direct = space.getDirect(address);
            device -> write(direct, data);
            return;
        }
    }
}
