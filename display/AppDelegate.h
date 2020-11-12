//
//  AppDelegate.h
//  display
//
//  Created by Артём Оконечников on 11.11.2020.
//

#import <Cocoa/Cocoa.h>
#include "Video.hpp"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, readonly) Video * video;
+ (AppDelegate *) sharedAppDelegate;
@end

