//
//  AppDelegate.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#include <iostream>
#include <cstdint>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>

#include "PagedBus.hpp"
#include "Video.hpp"
#include "i8080.hpp"

#import "AppDelegate.h"

#define OFFSET 0xF800

@interface AppDelegate ()
@end

@implementation AppDelegate

dispatch_queue_t _globalQueue;

Bus   * _bus   = new PagedBus();
i8080 * _cpu   = new i8080();

- (instancetype) init
{
    if (self = [super init])
    {
        _cpu   -> connect(_bus);
        _cpu   -> setCounter(OFFSET);
        
        _video = new Video();
        _video -> connect(_bus);
        
        _globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }
    
    return self;
}

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self loadMonitor];
    
    __block id _self = self;
    dispatch_async(_globalQueue, ^{
        [_self run];
    });
}

- (void) run
{
    using namespace std::chrono;
    
    const int    portion   = 10000;
    const long   frequency = 2500000;
    const double hzpersec  = 1.0 / frequency;

    auto start = steady_clock::now();
    auto begin = steady_clock::now();
    
    double overrun = 0;
    
    int count = 0;
    int freqcounter = 0;

    auto elapsd = [](steady_clock::time_point time)
    {
        return (duration<double>) (steady_clock::now() - time);
    };

    while (true)
    {
        if (count == portion)
        {
            duration<double> elapsed  = elapsd(start);
            double expected = portion * hzpersec;
            
            if (expected > elapsed.count())
            {
                double sleep = expected - elapsed.count();
                
                if ((overrun -= sleep) < 0)
                {
                    sleep = std::abs(overrun);
                    auto startSleep = steady_clock::now();

                    // Sleep
                    auto dur = duration<double>(sleep);
                    std::this_thread::sleep_for(dur);

                    // Count overrun
                    duration<double> elapsedSleep = elapsd(startSleep);
                    if (elapsedSleep.count() > sleep)
                    {
                        overrun = elapsedSleep.count() - sleep;
                    }
                }
            }
            
            count = 0;
            start = steady_clock::now();
        }
        
        if (freqcounter == 1000000)
        {
            duration<double> time = elapsd(begin);
            _freq = 1.0 / time.count();
            
            std::cout.precision(3);
            std::cout << (1.0 / time.count()) << " Mhz ";
            std::cout << time.count()         << " sec";
            std::cout << std::endl;
            
            freqcounter = 0;
            begin = steady_clock::now();
        }
        
        // Cpu cycle
        _cpu -> clock();
        
        // Counters
        count++;
        freqcounter++;
    }
}

- (void) loadMonitor
{
    std::ifstream file("/Users/temaweb/Desktop/Орион-128/Orion-128/monitor/RAM_TEST.bin", std::ios::in | std::ios::binary);
    uint16_t offset = OFFSET;
    
    char buffer = 0x00;
    while (!file.eof())
    {
        file.read(&buffer, 1);
        _bus -> write(offset++, buffer);
    }

    file.close();
}

- (void) applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

+ (AppDelegate *) sharedAppDelegate {
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}

@end
