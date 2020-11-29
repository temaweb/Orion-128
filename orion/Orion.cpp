//
//  Orion.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include <chrono>
#include <thread>

#include "Orion.hpp"

#include "IOSplitter.hpp"
#include "IOController.hpp"

#include "System.hpp"
#include "Disk.hpp"
#include "MonitorRom.hpp"

#include "PageSelector.hpp"
#include "PaletteSelector.hpp"
#include "ScreenSelector.hpp"

using namespace std::chrono;

Orion::Orion()
{
    // Construct IO storages
    
    auto iobus = std::make_shared<IOBus>();
    auto iocnt = std::make_shared<IOController> (iobus);
    auto iospl = std::make_shared<IOSplitter>   (iocnt);
    
    // Construct bus
    
    iobus -> insertR  <MonitorRom>();
    iobus -> insertRW <System>();
    iobus -> insertRW (memory);
    
    // Constuct IO devices
    
    iocnt -> insertW  <PageSelector>    (memory);
    iocnt -> insertW  <PaletteSelector> (video);
    iocnt -> insertW  <ScreenSelector>  (video);
    iocnt -> insertRW <Disk>();
    iocnt -> insertRW (keyboard);
    
    // Connect video memory
    
    video -> connect(memory);
    
    // Connect IOSplitter and IOController
    
    cpu   -> connect(iocnt);
    cpu   -> connect(iospl);
}

// Main loop at @frequency Hz
void Orion::run(int frequency)
{
    auto clock = 0;
    auto start = steady_clock::now();

    auto hzclock = 0;
    auto hztimer = steady_clock::now();
    
    auto frame = 0;
    
    while (isRunning)
    {
        if (clock == cycle)
        {
            delay(start, frequency);
            reset(start, clock);
        }

        if (hzclock == frequency)
        {
            currfreq = frequencyRate(hztimer, frequency);
            reset(hztimer, hzclock);
        }

        if (frame == freq)
        {
            video -> createFrame();
            frame = 0;
        }
        
        cpu -> clock();
        
        frame++;
        clock++;
        hzclock++;
    }
}

void Orion::reset(timepoint & start, int & clock)
{
    clock = 0;
    start = steady_clock::now();
}

double Orion::frequencyRate(const timepoint & start, const int & frequency)
{
    auto elapsed = timepassed(start);
    return frequency / elapsed;
}

void Orion::stop()
{
    isRunning = false;
}

#pragma mark -
#pragma mark Delay

void Orion::delay(const timepoint start, const int frequency)
{
    auto elapsed  = timepassed(start);
    auto expected = (1.0 / frequency) * cycle;
    
    if (elapsed >= expected)
        return;
        
    double sleep = expected - elapsed;
    
    // If previos iteration thread was sleep more that need
    // then current sleep time substract from this oversleep
    if ((oversleep -= sleep) >= 0)
        return;
    
    this -> delay();
}

void Orion::delay()
{
    auto sleep = std::abs(oversleep);
    auto start = steady_clock::now();

    // Sleep current thread for overrun remainder
    std::this_thread::sleep_for(
       duration<double>(sleep)
    );

    // Count overrun if thread sleep more that need
    auto delay = timepassed(start);
    if (delay > sleep)
    {
        oversleep = delay - sleep;
    }
}

#pragma mark -
#pragma mark Other

double Orion::timepassed(const timepoint start)
{
    duration<double> elapsed = steady_clock::now() - start;
    return elapsed.count();
}

// Create document in B:
void Orion::createFile(std::string path)
{
    filesystem -> create(path);
}

void Orion::keyevent(unsigned short code, bool isPressed)
{
    keyboard -> keyevent(code, isPressed);
}

// Return current loop frequency
double Orion::getFrequency()
{
    return currfreq;
}
