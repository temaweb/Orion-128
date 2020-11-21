//
//  OrionFacade.m
//  Orion
//
//  Created by Артём Оконечников on 20.11.2020.
//

#include "Orion.hpp"
#import "OrionFacade.h"

@implementation OrionFacade

#pragma mark -
#pragma mark private

std::unique_ptr<Orion> _orion = std::make_unique<Orion>();

#pragma mark -
#pragma mark public

- (double) getFrequency {
    return _orion -> getFrequency();
}

// Run loop
- (void) run {
    _orion -> run();
}

- (void) stop {
    _orion -> stop();
}

// Keyboard events
- (void) keyEvent: (unsigned short) code
        isPressed: (bool) isPressed
{
    _orion -> keyevent(code, isPressed);
}

// Open file and store in B:
- (void) load: (NSString *) path
{
    auto pathString = std::string([path UTF8String]);
    _orion -> createFile(pathString);
}

@end
