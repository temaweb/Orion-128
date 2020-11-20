//
//  Orion.cpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#include "Orion.hpp"
#include "Memory.hpp"
#include "MemorySwitch.hpp"
#include "PaletteSwitch.hpp"
#include "ScreenSwitch.hpp"
#include "RamtestRom.hpp"
#include "System.hpp"

#include <chrono>
#include <thread>
#include <cmath>

#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;
using namespace std::chrono;

Orion::Orion()
{
    //auto memory   = make_shared<Memory>();
    auto bus      = make_shared<Bus>();
    auto io       = make_shared<IOController>();
    auto switcher = make_shared<MemorySwitch>();
    auto color    = make_shared<PaletteSwitch>();
    
    color -> connect(video);
    
    bus -> connect<MonitorRom>();
    bus -> connect<System>();
    bus -> connect(memory);
    
    io -> connect(color);
    io -> connect<ScreenSwitch>();
    io -> connect<Disk>();
    io -> connect(keyboard);
    io -> connect(switcher);
    io -> connectBus(bus);
    
    switcher -> connect(memory);
    
    cpu   -> connect(io);
    video -> connect(memory);
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
    auto file = std::ifstream(path, std::ios::in | std::ios::binary);
    char buffer = 0x00;
    
    std::vector<uint8_t> mem;
    while (!file.eof())
    {
        file.read(&buffer, sizeof(buffer));
        mem.push_back(buffer);
    }
    
    file.close();
    
    int i = 0;
    for (i = 0; i < mem.size(); i++) {
        memory -> writeB(i, mem[i]);
    }
}
