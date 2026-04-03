//
//  NBSDiagnosisTask.h
//  NBSAppAgent
//
//  Created by tgf on 2023/6/14.
//

#import <Foundation/Foundation.h>
#import "NBSDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface NBSTaskCondition : NSObject<NBSSerializable>
NBS_NO_INIT
/**
 * Trigger scene, e.g., fire after network error.
 */
@property (nonatomic, assign) NBSDiagnosisTaskScene scene;
/**
 * When a network request completes or fails, only URIs matching patternDomains will execute. If nil, no restriction.
 */
@property (nonatomic, strong) NSArray <NSString *>*patternDomains;
/**
 * Only request errors included in patternErrorCodes will execute. If nil, no restriction.
 */
@property (nonatomic, strong) NSArray <NSNumber *>*patternErrorCodes;

- (instancetype)initWithScene:(NBSDiagnosisTaskScene)scene;

@end

@interface NBSDiagnosisTask : NSObject<NBSSerializable>
NBS_NO_INIT
/**
 * Host address.
 */
@property (nonatomic, copy) NSString *host;

/**
 * Match condition.
 */
@property (nonatomic, strong) NBSTaskCondition *condition;

/**
 * Execution interval; default 60s. Identical task runs at most once within this window.
 */
@property (nonatomic, assign) NSInteger execFrequency;

@end

@interface NBSTCPPingDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
/**
 * Port.
 */
@property (nonatomic ,assign) NSInteger port;
/**
 * Repeat count per TCP ping task; default 3.
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
 * Repeat count per ICMP ping task; default 3.
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
 * downloadTask does not support conditional execution.
 */
@interface NBSDownloadDiagnosisTask : NBSDiagnosisTask
NBS_NO_INIT
/**
 * Download URL.
 */
@property (nonatomic, copy) NSString *url;

+ (instancetype)downloadTaskWithName:(NSString *)name
                                 url:(NSString *)url;
@end
NS_ASSUME_NONNULL_END
