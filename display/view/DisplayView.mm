//
//  NSObject+DisplayView.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import "DisplayView.h"
#import "AppDelegate.h"

#include "Graphics.hpp"
#include "Video.hpp"

#define FPS 60.0f

@implementation DisplayView
{
@private
    std::shared_ptr<Video> video;
    std::unique_ptr<Graphics> graphics;
    
    // Frame timer
    NSTimer * timer;
}

- (instancetype) initWithCoder:(NSCoder *)coder
{
    if (self = [super initWithCoder: coder]) {
        [self setItemPropertiesToDefault: self];
    }
    
    return self;
}

- (void) setItemPropertiesToDefault:sender
{
    timer = [self createDisplayTimer];
    
    video = [[AppDelegate sharedAppDelegate] video];
    graphics = std::make_unique<Graphics>(video);
    
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

#pragma mark -
#pragma mark Drawing

- (void) prepareOpenGL
{
    [super prepareOpenGL];
    graphics -> initialize();
}

- (void) drawRect: (NSRect) rect
{
    graphics -> render(NSWidth(rect), NSHeight(rect));
}

#pragma mark -
#pragma mark Timer

- (NSTimer *) createDisplayTimer
{
    return  [NSTimer timerWithTimeInterval: (1.0 / FPS)
                                             target:self
                                           selector:@selector(updateTimer:)
                                           userInfo:nil
                                            repeats:YES];
}

- (void) updateTimer:(NSTimer *) theTimer
{
    [self setNeedsDisplay: video -> isChanged()];
}

@end
