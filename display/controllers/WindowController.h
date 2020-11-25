//
//  NSObject+WIndowController.h
//  display
//
//  Created by Артём Оконечников on 13.11.2020.
//

#import <Cocoa/Cocoa.h>

@interface WindowController : NSWindowController

- (IBAction)discardAction:(id)sender;
- (IBAction)openExecutable:(id)sender;

@property (nonatomic) NSString * title;
@end

