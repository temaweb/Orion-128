//
//  Orion.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include "Orion.hpp"
#include "Bus.hpp"
#include "Memory.hpp"
#include "Switcher.hpp"
#include "VideoObserver.hpp"
#include "IOController.hpp"
#include "IOSplitter.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono;

Orion::Orion()
{
    auto bus = std::make_shared<Bus>();
    auto io = std::make_shared<IOController>();
    auto switcher = std::make_shared<Switcher>();
    auto iosplitter = std::make_shared<IOSplitter>(io);
    
    switcher -> connect(video);
    switcher -> connect(memory);

    bus -> connect(memory);
    
    io -> connect(switcher);
    io -> connect(keyboard);
    io -> connect(bus);
    
    cpu   -> connect(io);
    cpu   -> connect(iosplitter);
    video -> connect(memory);
    
    filesystem = std::make_unique<Filesystem>(memory);
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
