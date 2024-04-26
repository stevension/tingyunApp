//
//  NBSDiagnosisTask.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2023/6/14.
//

#import <Foundation/Foundation.h>
#import "NBSDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface NBSTaskCondition : NSObject<NBSSerializable>
NBS_NO_INIT
/**
 * 触发场景：如网络错误后触发*
 */
@property (nonatomic, assign) NBSDiagnosisTaskScene scene;
/**
 * 当网络请求完成或出错时，uri只有符合patternDomain中的才会执行，不设置则默认不受此限制
 */
@property (nonatomic, strong) NSArray <NSString *>*patternDomains;
/**
 * 包含在patternErrorCodes中的请求错误才会执行，不设置则默认不受此限制
 */
@property (nonatomic, strong) NSArray <NSNumber *>*patternErrorCodes;

- (instancetype)initWithScene:(NBSDiagnosisTaskScene)scene;

@end

@interface NBSDiagnosisTask : NSObject<NBSSerializable>
NBS_NO_INIT
/**
 * 主机地址
 */
@property (nonatomic, copy) NSString *host;

/**
 * 匹配条件
 */
@property (nonatomic, strong) NBSTaskCondition *condition;

/**
 * 执行间隔，默认60秒，即60秒内相同任务最多执行一次
 */
@property (nonatomic, assign) NSInteger execFrequency;

@end

@interface NBSTCPPingDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
/**
 * 端口
 */
@property (nonatomic ,assign) NSInteger port;
/**
 * 一次tcpping任务重复的次数，默认3次
 */
@property (nonatomic, assign) NSInteger repeat;


+ (instancetype)tcppingTaskWithName:(NSString *)name
                               host:(NSString *)host
                               port:(NSInteger)port;

+ (instancetype)tcppingTaskWithName:(NSString *)name
                               host:(NSString *)host
                               port:(NSInteger)port
                          condition:(nullable NBSTaskCondition *)condition;

@end

@interface NBSICMPPingDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
/**
 * 一次icmpping任务重复的次数，默认3次
 */
@property (nonatomic, assign) NSInteger repeat;

+ (instancetype)icmppingTaskWithName:(NSString *)name
                                host:(NSString *)host;

+ (instancetype)icmppingTaskWithName:(NSString *)name
                                host:(NSString *)host
                           condition:(nullable NBSTaskCondition *)condition;

@end

@interface NBSMTRDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
+ (instancetype)mtrTaskWithName:(NSString *)name
                           host:(NSString *)host;

+ (instancetype)mtrTaskWithName:(NSString *)name
                           host:(NSString *)host
                      condition:(nullable NBSTaskCondition *)condition;

@end

/**
 * dowloadTask 不支持指定条件的任务
 */
@interface NBSDownloadDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
/**
 * 下载地址 *
 */
@property (nonatomic, copy) NSString *url;

+ (instancetype)downloadTaskWithName:(NSString *)name
                                 url:(NSString *)url;
@end
NS_ASSUME_NONNULL_END
