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

#include "IOBus.hpp"
#include "Cpu.hpp"
#include "Video.hpp"
#include "Keyboard.hpp"
#include "Memory.hpp"
#include "Filesystem.hpp"

class Orion
{
private:
    
    static const unsigned int  cycle = 10000;
    static const unsigned int  mhz   = 1000000;
    static const unsigned int  freq  = 5000;
    
    typedef std::chrono::steady_clock::time_point timepoint;
    
private:
    
    bool isRunning = true;
    
    double frequency = 0.0;
    double oversleep = 0.0;
    double currfreq  = 0.0;
    
    double timepassed(const timepoint start);
    double frequencyRate(const timepoint & start, const int & frequency);
    
    void delay();
    void delay(const timepoint start, const int frequency);
    void reset(timepoint & start, int & clock);
    
private:
    
    std::unique_ptr<Cpu>           cpu = std::make_unique<Cpu>();
    std::shared_ptr<Video>       video = std::make_unique<Video>();
    std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>();
    std::shared_ptr<Memory>     memory = std::make_shared<Memory>();
    std::unique_ptr<Filesystem> filesystem = std::make_unique<Filesystem>(memory);
    
public:
    Orion();
    
    // Return current loop frequency
    double getFrequency();

    // Run main loop at 2.5 MHz
    void run(int frequency = 2500000);
    void stop();
    
    // Process keyboard events
    void keyevent(unsigned short code, bool isPressed);
    
    // Load programm into Orion
    void createFile(std::string path);
    
    // Return video adapter
    std::shared_ptr<Video> getVideo() const
    {
        return video;
    }
    
    // Return video adapter
    std::shared_ptr<Keyboard> getKeyboard() const
    {
        return keyboard;
    }
};

#endif /* Orion_hpp */
