//
//  Orion.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include "Orion.hpp"

#include "Memory.hpp"
#include "Switcher.hpp"
#include "Bus.hpp"
#include "IOController.hpp"

#include <chrono>
#include <thread>
#include <cmath>

#include <fstream>
#include <vector>
#include <cstdint>

// #include "Disk.hpp"

using namespace std;
using namespace std::chrono;

Orion::Orion()
{
    auto bus      = make_shared<Bus>();
    auto io       = make_shared<IOController>();
    auto switcher = make_shared<Switcher>();
    
    switcher -> connect(video);
    switcher -> connect(memory);

    bus -> connect(memory);

    io -> connect(keyboard);
    io -> connect(switcher);
    io -> connect(bus);
    
    cpu   -> connect(io);
    video -> connect(memory);
    
    filesystem = std::make_unique<Filesystem>(memory);
}

// Main loop at @frequency Hz
void Orion::run(int frequency)
{
    auto count = 0;
    auto start = steady_clock::now();
    
    while (isRunning)
    {
        if (count == cycle)
        {
            delay(start, frequency);
            
            count = 0;
            start = steady_clock::now();
        }

        cpu -> clock();
        count++;
    }
}

void Orion::stop()
{
    isRunning = false;
}

#pragma mark -
#pragma mark Delay

void Orion::delay(const timepoint & start, const int & frequency)
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
    this_thread::sleep_for(
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

double Orion::timepassed(const timepoint & start)
{
    duration<double> elapsed = steady_clock::now() - start;
    return elapsed.count();
}

// Create document in B:
void Orion::openDocument(std::string path)
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
    return frequency;
}
