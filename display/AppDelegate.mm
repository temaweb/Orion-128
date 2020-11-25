//
//  AppDelegate.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#include "Orion.hpp"
#include "RamtestRom.hpp"

#import "AppDelegate.h"

@implementation AppDelegate
{
@private
    
    id monitor;
    
    dispatch_queue_t _globalQueue;
    std::shared_ptr<Orion> orion;
}

- (instancetype) init
{
    if (self = [super init]) {
        orion = std::make_shared<Orion>();
        _globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }
    
    return self;
}

- (double) getFrequency {
    return orion -> getFrequency();
}

- (std::shared_ptr<Video>) video {
    return orion -> getVideo();
}

- (std::shared_ptr<Keyboard>) keyboard {
    return orion -> getKeyboard();
}

- (std::shared_ptr<Orion>) orion {
    return orion;
}

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{   
    __block id _self = self;
    
    dispatch_async(_globalQueue, ^{
        [_self run];
    });
    
    id monitorHandler = ^NSEvent * (NSEvent * theEvent)
    {
        bool isPressed = [theEvent type] == NSEventTypeKeyDown;
        [_self keyboard] -> keyevent([theEvent keyCode], isPressed);
        
        // Return the event, a new event, or, to stop
        // the event from being dispatched, nil
        return theEvent;
    };

    // Creates an object we do not own, but must keep track of so that
    // it can be "removed" when we're done; therefore, put it in an ivar.
    monitor = [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskKeyDown | NSEventMaskKeyUp
                                                    handler:monitorHandler];
    
}

- (void) run {
    orion -> run();
}

- (void) applicationWillTerminate:(NSNotification *)aNotification
{
    [NSEvent removeMonitor: monitor];
    orion -> stop();
}

+ (AppDelegate *) sharedAppDelegate {
    return (AppDelegate *) [NSApplication sharedApplication].delegate;
}

@end
