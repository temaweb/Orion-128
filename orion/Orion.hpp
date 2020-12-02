/*
 * This file is part of the Orion-128 distribution (https://github.com/temaweb/orion-128).
 * Copyright (c) 2020 Artem Okonechnikov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Orion_hpp
#define Orion_hpp

#include "Cpu.hpp"
#include "Video.hpp"
#include "Keyboard.hpp"
#include "Loop.hpp"
#include "Filesystem.hpp"

#include "IOBus.hpp"
#include "Memory.hpp"

#define ORION_CPU_FREQUENCY 2500000

#define DEVICE(type, name) \
    std::shared_ptr<type> name = std::make_shared<type>()

class Orion
{
private:
    
    DEVICE(Cpu, cpu);
    DEVICE(Video, video);
    DEVICE(Keyboard, keyboard);
    DEVICE(Memory, memory);
    DEVICE(IOBus, iobus);
    
private:
    
    std::unique_ptr<Loop> loop = nullptr;
    std::unique_ptr<Filesystem> filesystem = nullptr;
    
    int actualFrequency = 0;

private:
    
    void createMemory();
    void createDevices();
    void createSwitches();
    
public:
    Orion();
    
    // Return current loop frequency
    double getFrequency() const;
    
    // Return video adapter
    std::shared_ptr<Video> getVideo() const;
    
    void run  (int frequency = ORION_CPU_FREQUENCY);
    void stop ();
    
    // Process keyboard events
    void keyevent(unsigned short code, bool isPressed);
    
    // Load programm into Orion
    void createFile(std::string path);
};

#endif /* Orion_hpp */
