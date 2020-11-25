//
//  AppDelegate.h
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import <Cocoa/Cocoa.h>

#include "Orion.hpp"
#include "Video.hpp"
#include "Keyboard.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, readonly, getter=getFrequency) double frequency;

@property (nonatomic, readonly) std::shared_ptr<Video> video;
@property (nonatomic, readonly) std::shared_ptr<Keyboard> keyboard;
@property (nonatomic, readonly) std::shared_ptr<Orion> orion;

+ (AppDelegate *) sharedAppDelegate;
@end

