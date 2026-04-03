//
//  NBSSerializableProtocol.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2021/11/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol NBSSerializable <NSObject>

- (NSDictionary<NSString *, id> *)serialize;

@end

NS_ASSUME_NONNULL_END
