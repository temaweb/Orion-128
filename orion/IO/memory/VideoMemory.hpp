//
//  VideoMemory.hpp
//  orion
//
//  Created by Артём Оконечников on 26.11.2020.
//

#ifndef VideoMemory_hpp
#define VideoMemory_hpp

#include <stdio.h>
#include <cstdint>
#include <array>

#include "Memory.hpp"
#include "IODevice.hpp"

class VideoMemory
{
private:
    
    constexpr static Space screens[4]
    {
        { 0xC000, 0xEFFF },
        { 0x8000, 0xAFFF },
        { 0x4000, 0x6FFF },
        { 0x0000, 0x2FFF }
    };
    
private:
    
    uint8_t screen = 0;
    std::shared_ptr<const Memory> memory;
    
public:
    
    VideoMemory(std::shared_ptr<const Memory> memory);
    
    std::array<uint8_t, 12 * 1024> getFrame() const;
    std::array<uint8_t, 12 * 1024> getColor() const;
    
    void setScreen(uint8_t screen);
    Space getScreen() const;
};

#endif /* VideoMemory_hpp */
