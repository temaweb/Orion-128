//
//  AppDelegate.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#include "Orion.hpp"
#include "RamtestRom.hpp"

#import "AppDelegate.h"


@interface AppDelegate ()
@end

@implementation AppDelegate

dispatch_queue_t _globalQueue;
id monitor;
std::shared_ptr<Orion> orion = std::make_shared<Orion>();

- (instancetype) init
{
    if (self = [super init]) {
        _globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }
    
    return self;
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

- (double) freq {
    return orion -> getFrequency();
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

- (void) applicationWillTerminate:(NSNotification *)aNotification {
    [NSEvent removeMonitor: monitor];
}

+ (AppDelegate *) sharedAppDelegate {
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}

@end
