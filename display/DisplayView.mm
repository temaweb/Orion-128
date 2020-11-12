//
//  NSObject+DisplayView.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import "DisplayView.h"
#import "AppDelegate.h"

#include <cstdint>
#include <vector>

#include "Video.hpp"

@implementation DisplayView

Video   * video;
NSTimer * timer;

CGFloat width;
CGFloat height;

- (void) drawRect: (NSRect) rect
{
    [self setColors:rect];
    [super drawRect:rect];
    
    width  = rect.size.width;
    height = rect.size.height;
    
    if (timer == NULL) {
        timer = [self createDisplayTimer];
    }

    video = [self getVideo];
    
    // Draw lines
    
    int row = 0;
    for (std::vector<Pixel> & line : video -> output())
    {
        int col = 0;
        for (auto & pixel : line)
        {
            [self drawPixel:pixel column:col row:row];
            col++;
        }
        
        row++;
        col = 0;
    }
}

#pragma mark -
#pragma mark Draw pixel

- (void) drawPixel: (Pixel) pixel
            column: (int) col
               row: (int) row
{
    auto resolution = video -> getResolution();
    
    CGFloat pixelHeight = height / resolution.height;
    CGFloat pixelWidth  = width  / resolution.width;

    [self setColor: pixel];
    
    CGFloat x = col * pixelWidth;
    CGFloat y = height - ((row * pixelHeight) + pixelHeight);
    
    [NSBezierPath fillRect:NSMakeRect(x, y, pixelWidth, pixelHeight)];
}

- (void) setColor: (Pixel) pixel
{
    NSColor * color = [NSColor colorWithCalibratedRed:(CGFloat) pixel.getRed()
                                                green:(CGFloat) pixel.getGreen()
                                                 blue:(CGFloat) pixel.getBlue()
                                                alpha:1.0f];
    
    [color set];
}

- (void) setColors: (NSRect) rect
{
    [[NSColor blackColor] setFill];
    NSRectFill(rect);
}

- (Video *) getVideo
{
    return [[AppDelegate sharedAppDelegate] video];
}

#pragma mark -
#pragma mark Timer

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
    [self setNeedsDisplay:YES];
}

@end
