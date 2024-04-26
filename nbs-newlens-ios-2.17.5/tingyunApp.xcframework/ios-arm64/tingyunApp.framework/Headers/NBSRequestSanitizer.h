//
//  NBSRequestSanitizer.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2023/9/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NBSRequestSanitizer : NSObject

@property (nonatomic, assign) BOOL enabled;

+ (instancetype)sanitizer;

- (void)setRequestHeaderSanitizionWithBlock:(nullable NSDictionary *_Nullable (^)(NSURL *url, NSDictionary *allHTTPHeaderFields))block;

- (void)setRequestBodySanitizionWithBlock:(nullable NSString * _Nullable (^) (NSURL *url, NSDictionary *allHTTPHeaderFields, NSData *body))block;

- (NSDictionary *)headersBySanitizingUrl:(NSURL *)url
                         httpHeaderFields:(NSDictionary *)allHeaderFields;
- (NSString *)bodyStringBySanitizingUrl:(NSURL *)url
                        httpHeaderFields:(NSDictionary *)allHeaderFields
                             requestBody:(NSData *)body;

@end

NS_ASSUME_NONNULL_END
