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

#include <iostream>
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
    
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

#pragma mark -
#pragma mark Drawing

- (void) drawRect: (NSRect) rect
{
    glClearColor(0, 0, 0, 0);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix ();
    
    glOrtho(0, NSWidth(rect), 0, NSHeight(rect), -1.0, 1.0);
    
    auto resolution   = video -> getResolution();
    
    float pixelHeight = (NSHeight(rect) - resolution.height) / resolution.height;
    float pixelWidth  = (NSWidth(rect)  - resolution.width)  / resolution.width;
    
    // Current pixel
    int index = 0x00;
    
    // Total pixels
    int total = resolution.height * resolution.width;
    
    // GL Arrays
    float * vertices = nullptr;
    float * colors   = nullptr;
    
    // Array size
    uint16_t size  = 0x00;
    uint16_t limit = 65535;
    
    // Shapes per pixel
    static int shapes = 18;
    
    int row = 0;
    for (auto & line : video -> output())
    {
        int col = 0;
        for (auto & pixel : line)
        {
            if ((index * shapes) == size)
            {
                int max = (limit - (limit % shapes));
                
                if (total >= (max / shapes))
                {
                    size = max;
                }
                else
                {
                    size = (total * shapes);
                }
                
                vertices = new float[size];
                colors   = new float[size];
                
                index = 0;
            }
            
            CGFloat x = (col * pixelWidth) + col;
            CGFloat y = (NSHeight(rect) - ((row * pixelHeight) + pixelHeight)) - row;
            
            int vertexindex = index * shapes;
            
            for (int i = 0, j = 0; i < 6; i++)
            {
                colors[vertexindex + j++] = pixel.getRed   ();
                colors[vertexindex + j++] = pixel.getGreen ();
                colors[vertexindex + j++] = pixel.getBlue  ();
            }
            
            // Triangles vertices
            
            vertices[vertexindex + 0]  = x;
            vertices[vertexindex + 1]  = y;
            vertices[vertexindex + 2]  = 0;

            vertices[vertexindex + 3]  = x;
            vertices[vertexindex + 4]  = y + pixelHeight;
            vertices[vertexindex + 5]  = 0;

            vertices[vertexindex + 6]  = x + pixelWidth;
            vertices[vertexindex + 7]  = y + pixelHeight;
            vertices[vertexindex + 8]  = 0;

            vertices[vertexindex + 9]  = x;
            vertices[vertexindex + 10] = y;
            vertices[vertexindex + 11] = 0;

            vertices[vertexindex + 12] = x + pixelWidth;
            vertices[vertexindex + 13] = y + pixelHeight;
            vertices[vertexindex + 14] = 0;

            vertices[vertexindex + 15] = x + pixelWidth;
            vertices[vertexindex + 16] = y;
            vertices[vertexindex + 17] = 0;
            
            if (--total == 0 || ((index + 1) * shapes) == size)
            {
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(3, GL_FLOAT, 0, colors);

                glDrawArrays(GL_TRIANGLES, 0, (size / 3));
                glDisableClientState(GL_VERTEX_ARRAY);
                
                delete[] vertices;
                delete[] colors;
            }
            
            index++;
            col++;
        }

        row++;
    }
    
    glPopMatrix ();
    glFlush ();
}

#pragma mark -
#pragma mark Timer

- (NSTimer *) createDisplayTimer
{
    return  [NSTimer timerWithTimeInterval: (NSTimeInterval)(1.0 / 60.0)
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
