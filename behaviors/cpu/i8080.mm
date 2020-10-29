//
//  i8080.m
//  behaviors
//
//  Created by Артём Оконечников on 29.10.2020.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

#import "Bus.hpp"
#import "i8080.hpp"

@interface i8080Behaviors : XCTestCase
@end

@implementation i8080Behaviors

Bus * _bus;
i8080 * _cpu;

- (void) setUp
{
    _bus = new Bus();
    _cpu = new i8080();
    
    _cpu -> connect(_bus);
}

- (void) tearDown
{
    delete _cpu;
    delete _bus;
}

#pragma mark -


- (void) testExecuteXXX
{
    // XXX
}

// Code: NOP
// Operation: No-operation
- (void) testExecuteNOP
{
    // NOP
}

@end
