//
//  NBSSpan.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2021/11/22.
//

#import <Foundation/Foundation.h>
#import "NBSDefines.h"
#import "NBSSerializableProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@class NBSTracer;
@class NBSSpanContext;

@protocol NBSSpan <NBSSerializable>

/**
 * The context information of the span.
 */
@property (nonatomic, readonly) NBSSpanContext *context;

/**
 * The timestamp of which the span ended.
 */
@property (nullable, nonatomic, strong, readonly) NSDate *endTimestamp;

/**
 * The start time of the span.
 */
@property (nullable, nonatomic, strong, readonly) NSDate *startTimestamp;

/**
 * Whether the span is finished.
 */
@property (readonly) BOOL isFinished;

/**
 * The Transaction this span is associated with.
 */
@property (nullable, nonatomic, readonly, strong) id<NBSSpan> transaction;

/**
 * @brief 创建一个子span
 * @param name 名称；不能为空，长度限制为1024字符，超过截取前1024字符
 * @param operation 类别；不能为空，长度限制为128字符，超过截取前128字符
 */
- (id<NBSSpan>)startChildWithName:(NSString *)name operation:(NSString *)operation;

/**
 * @brief 创建一个带description「描述」的子span
 * @param name 名称；不能为空，长度限制为1024字符，超过截取前1024字符。
 * @param operation 类别；不能为空，长度限制为128字符，超过截取前128字符
 * @param description 描述；长度限制为1024字符，超过截取前1024字符
 */
- (id<NBSSpan>)startChildWithName:(NSString *)name operation:(NSString *)operation description:(nullable NSString *)description;

/**
 * @brief 设置data的值
 */
- (void)setDataValue:(nullable id)value forKey:(NSString *)key;

/**
 * @brief 从data中移除
 */
- (void)removeDataForKey:(NSString *)key;

/**
 * @brief 设置tags的值
 * @warning value类型必须为字符串
 */
- (void)setTagValue:(NSString *)value forKey:(NSString *)key;

/**
 * @brief 从tags中移除
 */
- (void)removeTagForKey:(NSString *)key;

/**
 * @brief 设置metrics的值，不设置value的单位，如需设置单位请使用接口
 * `- (void)setMetricValue:(NSNumber *)value unit:(NSString *)unit forKey:(NSString *)key;`
 * @warning value的类型必须为NSNumber
 * @discussion 当span的operation为websocket时，如果设置的是sendSize、sendCount、receiveSize、receiveCount、pingpongCount的值，SDK会自动累加
 */
- (void)setMetricValue:(NSNumber *)value forKey:(NSString *)key;

/**
 * @brief 设置metrics的值
 * @param unit value的单位名称，比如毫秒“ms”，保留单位类型见NBSDefines.h中的NBSSpanMetricUnitNames[ ]，支持自定义单位
 * @warning value的类型必须为NSNumber，unit的类型必须为字符串
 * @discussion 当span的operation为websocket时，如果设置的是sendSize、sendCount、receiveSize、receiveCount、pingpongCount的值，SDK会自动累加
 */
- (void)setMetricValue:(NSNumber *)value unit:(NSString *)unit forKey:(NSString *)key;

/**
 * @brief 从metrics中移除
 */
- (void)removeMetricForKey:(NSString *)key;

/**
 * @brief 主动设置transaction或span执行耗时
 * @param value transaction或span执行耗时
 */
- (void)setDuration:(NSNumber *)value;

/**
 * @brief 设置span的status
 */
- (void)setStatus:(NBSSpanStatus)status;

/**
 *@brief 出错时设置statusCode
 */
- (void)setStatusCode:(NSString *)value;

/**
 * @brief 完成一个span，并设置完成时间
 * @discussion 如果没有调用setSpanStatus:设置span的状态，span的状态默认为success
 */
- (void)finish;

/**
 * @brief 完成一个span并设置完成时间与span的状态
 */
- (void)finishWithStatus:(NBSSpanStatus)status;


@end

NS_ASSUME_NONNULL_END
