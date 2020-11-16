//
//  AppDelegate.h
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import <Cocoa/Cocoa.h>
#include "Video.hpp"
#include "Keyboard.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, readonly) std::shared_ptr<Video> video;
@property (nonatomic, readonly) std::shared_ptr<Keyboard> keyboard;

@property (nonatomic, readonly) double freq;

+ (AppDelegate *) sharedAppDelegate;
@end

