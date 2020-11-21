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

@interface DisplayView : NSView
{
    std::shared_ptr<Video> video;

    NSTimer * timer;

    CGFloat width;
    CGFloat height;
}

@end
