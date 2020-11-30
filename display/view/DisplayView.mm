//
//  NSObject+DisplayView.m
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import "DisplayView.h"
#import "AppDelegate.h"

#include <OpenGL/gl.h>
#include "Video.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

#define FPS 60.0f

@implementation DisplayView
{
@private
    std::shared_ptr<Video> video;
    std::shared_ptr<Orion> orion;
    
    // Frame timer
    NSTimer * timer;
    
    // Buffer objects
    GLuint vertexBuffer;
    GLuint colorBuffer;
}

- (instancetype) initWithCoder:(NSCoder *)coder
{
    if (self = [super initWithCoder: coder])
    {
        [self setItemPropertiesToDefault: self];
    }
    
    return self;
}

- (void) setItemPropertiesToDefault:sender
{
    timer = [self createDisplayTimer];
    
    video = [[AppDelegate sharedAppDelegate] video];
    orion = [[AppDelegate sharedAppDelegate] orion];
    
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

#pragma mark -
#pragma mark Drawing

- (void) prepareOpenGL
{
    [super prepareOpenGL];
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colorBuffer);
}

- (void) drawRect: (NSRect) rect
{
    glClearColor(0, 0, 0, 0);
    glClear ( GL_COLOR_BUFFER_BIT );

    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix ();
    
    glOrtho(0, NSWidth(rect), 0, NSHeight(rect), -1.0, 1.0);
    
    auto resolution   = video -> getResolution();
    
    float pixelHeight = (NSHeight(rect) - resolution.height) / resolution.height;
    float pixelWidth  = (NSWidth (rect) - resolution.width)  / resolution.width;
    
    // Current pixel
    int index = 0x00;
    
    // Total pixels
    int total = resolution.height * resolution.width;
    
    // GL Arrays
    float * vertices = nullptr;
    float * colors   = nullptr;
    
    // Array size
    uint16_t size  = 0x00;
    static uint16_t limit = 65535;
    
    // Shapes per pixel
    static int shapes = 12;
    
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
            
            int shape = index * shapes;
            
            float r = pixel.getRed();
            float g = pixel.getGreen();
            float b = pixel.getBlue();
            
            for (int i = 0, j = 0; i < 4; i++)
            {
                colors[shape + j++] = r;
                colors[shape + j++] = g;
                colors[shape + j++] = b;
            }
            
            // Squad vertex
            
            CGFloat x = (col * pixelWidth) + col;
            CGFloat y = (NSHeight(rect) - ((row * pixelHeight) + pixelHeight)) - row;
            CGFloat z = 0.0f;
            
            vertices[shape + 0]  = x;
            vertices[shape + 1]  = y + pixelHeight;
            vertices[shape + 2]  = z;

            vertices[shape + 3]  = x + pixelWidth;
            vertices[shape + 4]  = y + pixelHeight;
            vertices[shape + 5]  = z;

            vertices[shape + 6]  = x + pixelWidth;
            vertices[shape + 7]  = y;
            vertices[shape + 8]  = z;

            vertices[shape + 9]  = x;
            vertices[shape + 10] = y;
            vertices[shape + 11] = z;
            
            // Draw over VBO
            
            if (--total == 0 || ((index + 1) * shapes) == size)
            {
                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * size, vertices, GL_STATIC_DRAW);
                glVertexPointer(3, GL_FLOAT, 0, NULL);
                
                glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(*colors) * size, colors, GL_STATIC_DRAW);
                
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(3, GL_FLOAT, 0, NULL);
                
                glEnableClientState(GL_VERTEX_ARRAY);
                glDrawArrays(GL_QUADS, 0, size / 2);
                
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

#pragma clang diagnostic pop
