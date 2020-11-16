//
//  Orion.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include "Orion.hpp"

#include <chrono>
#include <thread>
#include <cmath>

using namespace std;
using namespace std::chrono;

Orion::Orion()
{
    cpu      -> connect(bus);
    video    -> connect(bus);
    keyboard -> connect(bus);
}

// Main loop at @frequency Hz
void Orion::run(int frequency)
{
    auto count = 0;
    auto start = steady_clock::now();
    
    while (true)
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

// Load data in read only memory at 0xF800 - 0xFFFF
void Orion::load(std::shared_ptr<Rom> rom)
{
    auto offset = rom -> getOffset();
    
    rom -> load(bus);
    cpu -> setCounter(offset);
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
