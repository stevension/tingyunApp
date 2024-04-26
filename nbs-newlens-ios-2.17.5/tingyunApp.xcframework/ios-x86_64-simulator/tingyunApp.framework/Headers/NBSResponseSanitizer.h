//
//  NBSResponseSanitizer.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2023/9/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NBSResponseSanitizer : NSObject

@property (nonatomic, assign) BOOL enabled;

+ (instancetype)sanitizer;

- (void)setResponseHeaderSanitizionWithBlock:(nullable NSDictionary *_Nullable (^)(NSHTTPURLResponse *response))block;
- (void)setResponseBodySanitizionWithBlock:(nullable NSString * _Nullable (^) (NSHTTPURLResponse *response,NSData *body))block;

- (NSDictionary *)headersBySanitizingResponse:(NSHTTPURLResponse *)response;
- (NSString *)bodyStringBySanitizingResponse:(NSHTTPURLResponse *)response responseBody:(NSData *)body;

@end

NS_ASSUME_NONNULL_END
