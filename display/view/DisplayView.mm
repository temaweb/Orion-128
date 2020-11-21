//
//  NSObject+DisplayView.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#include <cstdint>
#include <vector>

#include "Video.hpp"
#include "Keyboard.hpp"

#import "DisplayView.h"
#import "AppDelegate.h"

@implementation DisplayView

std::shared_ptr<Video> video = nullptr;

NSTimer * timer;

CGFloat width;
CGFloat height;

- (void) drawRect: (NSRect) rect
{
    [super drawRect:rect];

    if (timer == NULL) {
        timer = [self createDisplayTimer];
    }

    if (video == nullptr) {
        video = [[AppDelegate sharedAppDelegate] video];
    }

    width  = rect.size.width;
    height = rect.size.height;
    
    // Graphics
    
    NSGraphicsContext * gcontext = [NSGraphicsContext currentContext];
    CGContextRef context = [gcontext CGContext];
    
    // Background
    
    CGContextSetRGBFillColor(context, 0, 0, 0, 1);
    NSRectFill(rect);
    
    // Draw pixels
    
    int row = 0;
    for (std::vector<Pixel> & line : video -> output())
    {
        int col = 0;
        for (auto & pixel : line)
        {
            [self drawPixel:pixel
                    context:context
                     column:col
                        row:row];
            
            col++;
        }
        
        row++;
    }
}

#pragma mark -
#pragma mark Draw pixel

- (void) drawPixel: (Pixel) pixel
           context: (CGContextRef) context
            column: (int) col
               row: (int) row
{
    auto resolution = video -> getResolution();

    CGFloat pixelHeight = (height - resolution.height) / resolution.height;
    CGFloat pixelWidth  = (width  - resolution.width)  / resolution.width;

    CGContextSetRGBFillColor (context,
                              pixel.getRed(),
                              pixel.getGreen(),
                              pixel.getBlue(),
                              1.0f);
    
    CGFloat x = (col * pixelWidth) + col;
    CGFloat y = (height - ((row * pixelHeight) + pixelHeight)) - row;

    CGRect rectangle = CGRectMake (x, y, pixelWidth, pixelHeight);
    CGContextFillRect (context, rectangle);
}

#pragma mark -
#pragma mark Timer

- (NSTimer *) createDisplayTimer
{
    return  [NSTimer scheduledTimerWithTimeInterval:0.1f
                                             target:self
                                           selector:@selector(updateTimer:)
                                           userInfo:nil
                                            repeats:YES];
}

- (void) updateTimer:(NSTimer *)theTimer {
   [self setNeedsDisplay:YES];
}

@end
