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
std::unique_ptr<Orion> orion = std::make_unique<Orion>();

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

- (double) freq {
    return orion -> getFrequency();
}

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    orion -> load(std::make_shared<RamtestRom>());
    
    __block id _self = self;
    dispatch_async(_globalQueue, ^{
        [_self run];
    });
}

- (void) run {
    orion -> run();
}

- (void) applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

+ (AppDelegate *) sharedAppDelegate {
    return (AppDelegate *)[NSApplication sharedApplication].delegate;
}

@end
