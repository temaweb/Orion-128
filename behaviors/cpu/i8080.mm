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

/*
 
 NOP
 
 0000    00              nop
 0000:   00
 
 */
- (void) testNOP
{
    // Given
    _bus -> write(0x0000, 0x00);
    
    // When
    _cpu -> execute(4);
    
    // Then
    XCTAssertTrue(_bus -> read(0x00) == 0x00);
}

/*
 
 LXI B, D16
 
 0000    01 FF FF        lxi b, 0xFFFF
 0003    21 00 C0        lxi h, 0xC000
 0006    70              mov m, b
 0007    21 01 C0        lxi h, 0xC001
 000A    71              mov m, c
 
 0000:   01 FF FF 21 00 C0 70 21 01 C0 71
 
 */
- (void) testLXIB
{
    // Given
    _bus -> write("01 FF FF 21 00 C0 70 21 01 C0 71");
    
    // When
    _cpu -> execute(100);
    
    // Then
    XCTAssertTrue(_bus -> read(0xC000) == 0xFF);
    XCTAssertTrue(_bus -> read(0xC001) == 0xFF);
}

/*
 
 STAX B
 
 0000    3E FF           MVI a, 0xFF
 0002    01 00 C0        LXI b, 0xC000
 0005    02              STAX b
 
 0000:   3E FF 01 00 C0 02
 */
- (void) testSTAXB
{
    // Given
    _bus -> write("3E FF 01 00 C0 02");
    
    // When
    _cpu -> execute(100);
    
    // Then
    XCTAssertTrue(_bus -> read(0xC000) == 0xFF);
}

/*
 
 INX B
 
 0000    3E FF           MVI a, 0xFF
 0002    01 00 C0        LXI b, 0xC000
 0005    03              INX b
 0006    02              STAX b
 
 0000:  3E FF 01 00 C0 03 02
 */
- (void) testINXB
{
    // Given
    _bus -> write("3E FF 01 00 C0 03 02");
    
    // When
    _cpu -> execute(100);
    
    // Then
    XCTAssertTrue(_bus -> read(0xC001) == 0xFF);
}

- (void) testAC
{
    // Given
    _bus -> write("3E FF 06 FF 80");
    
    // When
    _cpu -> execute(10);
    
    // Then
}

@end
