//
//  NSObject+DisplayView.h
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import <Cocoa/Cocoa.h>

#include <cstdint>
#include <vector>
#include "Video.hpp"

#import "AppDelegate.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"

@interface DisplayView : NSOpenGLView
{
    std::shared_ptr<Video> video;

    NSTimer * timer;

    CGFloat width;
    CGFloat height;
}

@end

#pragma clang diagnostic pop
