//
//  VideoMemory.cpp
//  orion
//
//  Created by Артём Оконечников on 26.11.2020.
//

#include "VideoMemory.hpp"

VideoMemory::VideoMemory(std::shared_ptr<const Memory> memory) : memory(memory)
{ }

void VideoMemory::setScreen(uint8_t screen)
{
    this -> screen = screen & 0x03;
}

Space VideoMemory::getScreen() const
{
    return screens[screen];
}

#pragma mark -
#pragma mark Buffers

std::array<uint8_t, 12 * 1024> VideoMemory::getFrame() const
{
    return std::array<uint8_t, 12 * 1024>();
}

std::array<uint8_t, 12 * 1024> VideoMemory::getColor() const
{
    return std::array<uint8_t, 12 * 1024>();
}
