//
//  NSObject+WIndowController.m
//  display
//
//  Created by Артём Оконечников on 13.11.2020.
//

#import "WindowController.h"
#import "AppDelegate.h"

@implementation WindowController 

NSTimer * ttimer;

- (void) windowDidLoad
{
    [super windowDidLoad];
    
    if (ttimer == NULL) {
        ttimer = [self createDisplayTimer];
    }
}

- (NSTimer *) createDisplayTimer
{
    return  [NSTimer scheduledTimerWithTimeInterval:0.1
                                             target:self
                                           selector:@selector(updateTimer:)
                                           userInfo:nil
                                            repeats:YES];
}

- (void) updateTimer:(NSTimer *)theTimer
{
    double counter = [[AppDelegate sharedAppDelegate] freq];
    NSString * title = [NSString stringWithFormat:@"Орион-128 / %.01f MHz", counter];
    [[self window] setTitle:title];
}

@end
