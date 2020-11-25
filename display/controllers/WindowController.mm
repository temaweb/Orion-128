//
//  NSObject+WIndowController.m
//  display
//
//  Created by Артём Оконечников on 13.11.2020.
//

#define MHZ 1000000

#import "WindowController.h"
#import "AppDelegate.h"

@implementation WindowController
{
@private
    
    NSTimer * timer;
    AppDelegate * appDelegate;
}

- (void) windowDidLoad
{
    [super windowDidLoad];
    [self.window setAspectRatio:self.window.frame.size];
    
    appDelegate = [AppDelegate sharedAppDelegate];
    timer = [self createTimer];
}

#pragma mark -
#pragma mark Actions

- (IBAction) discardAction:(id)sender
{
    
}

- (IBAction) openExecutable:(id) sender
{
    NSOpenPanel * openDialog = [NSOpenPanel openPanel];

    [openDialog setCanChooseFiles:YES];
    [openDialog setAllowsMultipleSelection:NO];
    [openDialog setCanChooseDirectories:NO];

    [openDialog beginSheetModalForWindow:self.window
                       completionHandler:^(NSModalResponse result)
    {
        if (result != NSModalResponseOK)
            return;
        
        NSURL * file = [[openDialog URLs] firstObject];
        [self open: file.path];
    }];
}

- (void) keyDown:(NSEvent *) theEvent
{
    // Allow keyboard enter and switch off keyboard sound
}

- (void) open: (NSString *) path
{
    auto pathString = std::string([path UTF8String]);
    [appDelegate orion] -> createFile(pathString);
}

- (void) refreshTitle:(NSTimer *) theTimer
{
    NSString * title = NSLocalizedString(@"title", nil);
    title = [NSString stringWithFormat:title, appDelegate.frequency / MHZ];
    
    [self setTitle:title];
}

- (NSTimer *) createTimer
{
    return [NSTimer scheduledTimerWithTimeInterval:1.0f
                                            target:self
                                          selector:@selector(refreshTitle:)
                                          userInfo:nil
                                           repeats:YES];
}

@end
