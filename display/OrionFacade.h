//
//  OrionFacade.h
//  Orion
//
//  Created by Артём Оконечников on 20.11.2020.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface OrionFacade : NSObject

@property (readonly, getter=getFrequency) double frequency;

- (void) run;
- (void) stop;

- (void) load: (NSString *) path;
- (void) keyEvent: (unsigned short) code isPressed: (bool) isPressed;

@end

NS_ASSUME_NONNULL_END
