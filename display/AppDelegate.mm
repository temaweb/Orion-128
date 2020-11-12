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
    int c = 0;
    
    while (true)
    {
        if (c++ > 10000)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            c = 0;
        }

        _cpu -> clock();
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
