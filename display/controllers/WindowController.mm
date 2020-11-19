//
//  NSObject+WIndowController.m
//  display
//
//  Created by Артём Оконечников on 13.11.2020.
//

#import "WindowController.h"
#import "AppDelegate.h"

@implementation WindowController

- (void) windowDidLoad
{
    [super windowDidLoad];
}

- (NSString *) title
{
    double counter = [[AppDelegate sharedAppDelegate] freq];
    NSString * title = NSLocalizedString(@"title", nil);
    
    return [NSString stringWithFormat:title, counter];
}

- (void) keyDown:(NSEvent *) theEvent
{
    //[theEvent discardEditing];
}

@end
