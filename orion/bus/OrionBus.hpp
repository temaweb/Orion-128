//
//  OrionBus.hpp
//  orion
//
//  Created by Артём Оконечников on 12.11.2020.
//

#ifndef OrionBus_hpp
#define OrionBus_hpp

#include <cstdint>
#include <string>
#include <array>

#include "Bus.hpp"

class PagedBus : public Bus
{
private:
    
    const uint8_t  monitor = 0x00;
    const uint16_t sysport = 0xF900;
    
    uint8_t page = 0x00;
    
    std::array<uint8_t, 64 * 1024> ram[4];
    
public:
    PagedBus();
    
    uint8_t read(const uint16_t address) const override;
    void write(const uint16_t address, uint8_t data) override;
};

#endif /* OrionBus_hpp */
