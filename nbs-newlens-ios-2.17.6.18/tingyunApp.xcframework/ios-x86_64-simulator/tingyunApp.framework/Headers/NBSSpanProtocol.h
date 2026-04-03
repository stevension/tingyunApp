//
//  NBSSpan.h
//  NBSAppAgent
//
//  Created by tgf on 2021/11/22.
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
 * @brief Start a child span.
 * @param name Name; required; max 1024 characters (truncated if longer).
 * @param operation Operation/category; required; max 128 characters (truncated if longer).
 */
- (id<NBSSpan>)startChildWithName:(NSString *)name operation:(NSString *)operation;

/**
 * @brief Start a child span with description.
 * @param name Name; required; max 1024 characters (truncated if longer).
 * @param operation Operation/category; required; max 128 characters (truncated if longer).
 * @param description Description; max 1024 characters (truncated if longer).
 */
- (id<NBSSpan>)startChildWithName:(NSString *)name operation:(NSString *)operation description:(nullable NSString *)description;

/**
 * @brief Set a data value.
 */
- (void)setDataValue:(nullable id)value forKey:(NSString *)key;

/**
 * @brief Remove a value from data.
 */
- (void)removeDataForKey:(NSString *)key;

/**
 * @brief Set a tag value.
 * @warning Value must be a string.
 */
- (void)setTagValue:(NSString *)value forKey:(NSString *)key;

/**
 * @brief Remove a tag value.
 */
- (void)removeTagForKey:(NSString *)key;

/**
 * @brief Set a metric value without specifying unit; to set unit use
 * `- (void)setMetricValue:(NSNumber *)value unit:(NSString *)unit forKey:(NSString *)key;`
 * @warning Value must be NSNumber.
 * @discussion For websocket operations, sendSize/sendCount/receiveSize/receiveCount/pingpongCount are auto-accumulated.
 */
- (void)setMetricValue:(NSNumber *)value forKey:(NSString *)key;

/**
 * @brief Set a metric value with unit.
 * @param unit Unit name, e.g., ms; see NBSSpanMetricUnitNames[] in NBSDefines.h; custom units allowed.
 * @warning Value must be NSNumber; unit must be string.
 * @discussion For websocket operations, sendSize/sendCount/receiveSize/receiveCount/pingpongCount are auto-accumulated.
 */
- (void)setMetricValue:(NSNumber *)value unit:(NSString *)unit forKey:(NSString *)key;

/**
 * @brief Remove a metric.
 */
- (void)removeMetricForKey:(NSString *)key;

/**
 * @brief Manually set duration of transaction/span.
 * @param value Duration value.
 */
- (void)setDuration:(NSNumber *)value;

/**
 * @brief Set span status.
 */
- (void)setStatus:(NBSSpanStatus)status;

/**
 *@brief Set statusCode for errors.
 */
- (void)setStatusCode:(NSString *)value;

/**
 * @brief Finish a span and set end time.
 * @discussion If status not set via setSpanStatus:, default is success.
 */
- (void)finish;

/**
 * @brief Finish a span and set end time and status.
 */
- (void)finishWithStatus:(NBSSpanStatus)status;


@end

NS_ASSUME_NONNULL_END
