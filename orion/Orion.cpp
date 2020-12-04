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

#include "Orion.hpp"

#include "Disk.hpp"
#include "System.hpp"
#include "MonitorRom.hpp"
#include "RamtestRom.hpp"

#include "PageSelector.hpp"
#include "PaletteSelector.hpp"
#include "ScreenSelector.hpp"

#include "DelayEvent.hpp"
#include "FrameEvent.hpp"
#include "FreqEvent.hpp"

#include "IOSplitter.hpp"

Orion::Orion()
{
    vram  = memory -> getVideoRam();
    
    // IO Splitter process requests from CPU IN/OUT instructions
    auto iospl = std::make_shared<IOSplitter> (iobus);
    
    // Create basic memory
    //
    // 0x0000 - 0xF000 - 4 x 60 KB RAM
    // 0xF000 - 0xF400 - System RAM
    // 0xF800 - 0XFFFF - ROM BIOS (Monitor)
    
    createMemory();
    
    
    // Create devices
    //
    // 0xF400 - 0xF4FF - Keyboard (8x8 keys)
    // 0xF500 - 0xF5FF - ROM Disk (ORDOS)
    
    createDevices();
    
    
    // Connect video memory to video out
    //
    // 0xС000 — 0xEFFF - Screen #0 (Default)
    // 0x8000 — 0xAFFF - Screen #1
    // 0x4000 — 0x6FFF - Screen #2
    // 0x0000 — 0x2FFF - Screen #3
    
    video = std::make_shared<Video>(vram);
    
    
    // Create system switches
    //
    // 0xF800 - 0xF8FF - Color mode selector
    // 0xF900 - 0xF9FF - Memory pages switcher
    // 0xFA00 - 0xFAFF - Screen selector
    
    createSwitches();
    

    // Connect bus and splitter to CPU
    //
    // ALL    instructions → bus
    // IN/OUT instructions → splitter → bus
    
    cpu   -> connect(iobus);
    cpu   -> connect(iospl);

    // Set programm counter to begin of ROM
    cpu   -> setCounter (Rom<>::begin);
    
    // CP/M filesystem
    filesystem = std::make_unique<Filesystem>(memory);
}

void Orion::createMemory()
{
    // Monitor ROM (BIOS)
    //
    // 2 KB
    // 0xF800 - 0XFFFF (R/O)
    
    iobus -> createR  <MonitorRom> ();
    
    // System memory (System stack, etc)
    //
    // 2 KB
    // 0xF000 - 0xF400 (R/W)
    
    iobus -> createRW <System>();
    
    // Paged RAM (contains video memory)
    //
    // 4 x 60 KB
    // 0x0000 - 0xF000 (R/W)
    
    iobus -> insertRW (memory);
}

void Orion::createDevices()
{
    // Keyboard (8 x 8 matrix)
    //
    // 0xF400 - 0xF4FF (R/W)
    
    iobus -> insertRW (keyboard);
    
    // ROM disk (ORDOS)
    //
    // 0xF500 - 0xF5FF (R/W)
    
    iobus -> createRW <Disk>();
}

void Orion::createSwitches()
{
    // Color mode selector (B/W, Color4, 16...)
    //
    // System #1
    // 0xF800 - 0xF8FF (W/O)
    
    iobus -> createW  <PaletteSelector> (video);
    
    // Memory pages switcher
    //
    // System #2
    // 0xF900 - 0xF9FF (W/O)
    
    iobus -> createW  <PageSelector> (memory);
    
    // Video screen selector
    //
    // System #3
    // 0xFA00 - 0xFAFF (W/O)
    
    iobus -> createW  <ScreenSelector> (vram);
}

// Return current loop frequency
double Orion::getFrequency() const
{
    return actualFrequency;
}

std::shared_ptr<Video> Orion::getVideo() const
{
    return video;
}

void Orion::run(int frequency)
{
    // Create main CPU loop and add routines
    loop = std::make_unique<Loop>(cpu);
    
    // This event emulate 2.5 MHz loop (see @frequency)
    // Call every 10000 CPU clock
    loop -> create<DelayEvent> (frequency);
    
    // This event calculate actual loop frequency
    // Call every @frequency CPU clock
    loop -> create<FreqEvent>  (frequency, actualFrequency);
    
    // This event create video frame
    // Call every 5000 CPU clock
    loop -> create<FrameEvent> (video);

    // CPU run
    loop -> run();
}

void Orion::stop()
{
    loop -> hold();
}

void Orion::keyevent(unsigned short code, bool isPressed)
{
    keyboard -> keyevent(code, isPressed);
}

void Orion::createFile(std::string path)
{
    filesystem -> create(path);
}
