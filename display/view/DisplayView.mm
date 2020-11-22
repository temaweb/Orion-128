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

#include <OpenGL/gl.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

@implementation DisplayView

- (instancetype)initWithFrame:(NSRect)frameRect
{
    if (self = [super initWithFrame: frameRect]) {
        [self setItemPropertiesToDefault: self];
    }
    
    return self;
}

- (nullable instancetype)initWithCoder:(NSCoder *)coder
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
}

#pragma mark -
#pragma mark Drawing

- (void) reshape
{
    [super reshape];
    
    NSRect bounds = [self bounds];
    
    width  = bounds.size.width;
    height = bounds.size.height;

    glViewport ( 0, 0, (GLint) width, (GLint) height );

    glMatrixMode   ( GL_PROJECTION );
    glLoadIdentity ();

    glMatrixMode   ( GL_MODELVIEW );
    glLoadIdentity ();
    
    glOrtho(0, width, 0, height, -1.0, 1.0);
}

- (void) drawRect: (NSRect) rect
{
    glClearColor(0, 0, 0, 0);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix ();
    
    glBegin(GL_QUADS);
    
    auto resolution   = video -> getResolution();

    float pixelHeight = (height - resolution.height) / resolution.height;
    float pixelWidth  = (width  - resolution.width)  / resolution.width;
    
    int row = 0;
    for (std::vector<Pixel> & line : video -> output())
    {
        int col = 0;
        for (auto & pixel : line)
        {
            CGFloat x = (col * pixelWidth) + col;
            CGFloat y = (height - ((row * pixelHeight) + pixelHeight)) - row;

            glColor3f(pixel.getRed(), pixel.getGreen(), pixel.getBlue());
            
            glVertex2d(x, y + pixelHeight);
            glVertex2d(x + pixelWidth, y + pixelHeight);
            glVertex2d(x + pixelWidth, y);
            glVertex2d(x, y);

            col++;
        }

        row++;
    }
    
    glEnd();
    glPopMatrix ();
    glFlush ();
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

- (void) updateTimer:(NSTimer *) theTimer
{
   [self setNeedsDisplay:YES];
}

@end

#pragma clang diagnostic pop
