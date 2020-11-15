//
//  Orion.hpp
//  orion
//
//  Created by Артём Оконечников on 14.11.2020.
//

#ifndef Orion_hpp
#define Orion_hpp

#include <stdio.h>
#include <chrono>

#include "Cpu.hpp"
#include "Bus.hpp"
#include "Video.hpp"
#include "MonitorRom.hpp"

using namespace std::chrono;

typedef steady_clock::time_point timepoint;

class Orion
{
private:
    
    static const unsigned short cycle = 10000;
    static const unsigned int   mhz   = 1000000;
    
private:
    
    double frequency = 2.5;
    double oversleep = 0;
    
    double timepassed(const timepoint & start);
    
    void delay(const timepoint & start, const int & frequency);
    void delay();
    
private:
    
    std::shared_ptr<Bus>     bus = std::make_shared<Bus>();
    std::unique_ptr<Cpu>     cpu = std::make_unique<Cpu>();
    std::shared_ptr<Video> video = std::make_unique<Video>();

public:
    Orion();
    
    // Return video adapter
    std::shared_ptr<Video> getVideo() const
    {
        return video;
    }
    
    // Return current loop frequency
    double getFrequency()
    {
        return frequency;
    }
    
    // Load BIOS
    void load(std::shared_ptr<Rom> rom = std::make_shared<MonitorRom>());
    
    // Run main loop at 2.5 MHz
    void run(int frequency = 2500000);
};

#endif /* Orion_hpp */
