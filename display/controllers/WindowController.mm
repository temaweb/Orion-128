//
//  NSObject+WIndowController.m
//  display
//
//  Created by Артём Оконечников on 13.11.2020.
//

#import "WindowController.h"
#import "AppDelegate.h"

@implementation WindowController

AppDelegate * appDelegate;

- (void) windowDidLoad
{
    [super windowDidLoad];
    appDelegate = [AppDelegate sharedAppDelegate];
}

- (NSString *) title
{
    double counter = [appDelegate freq];
    NSString * title = NSLocalizedString(@"title", nil);
    
    return [NSString stringWithFormat:title, counter];
}

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

- (void) open: (NSString *) path
{
    auto pathString = std::string([path UTF8String]);
    [appDelegate orion] -> openDocument(pathString);
}

- (void) keyDown:(NSEvent *) theEvent
{
    
}

@end
