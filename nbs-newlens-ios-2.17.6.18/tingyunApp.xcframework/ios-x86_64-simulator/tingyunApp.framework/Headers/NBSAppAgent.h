//
//  NBSAppAgent.h
//
//  Created by yang kai on 14-3-12.
//  Copyright (c) 2014年 NBS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "NBSDefines.h"
#import "NBSSpanProtocol.h"
#import "NBSDiagnosisTask.h"
#import "NBSRequestSanitizer.h"
#import "NBSResponseSanitizer.h"

/**
 Record curl network info.
 */
void nbsGetCurlNetworkInfo(void *curl,int curlcode,void *ptr);


@interface NBSAppAgent : NSObject

/**
 *@brief Start NBSAppAgent; in most cases this is all you need.
 *@param appId Unique App ID from the Tingyun platform.
 */
+(void)startWithAppID:(NSString*)appId;

/**
 *@param appId Unique App ID from the Tingyun platform.
 *@param channelId Distribution channel ID.
 */
+(void)startWithAppID:(NSString *)appId channelId:(NSString *)channelId;

/**
 *@param appId Unique App ID from the Tingyun platform.
 *@param rate Launch probability between 0 and 1; 0.5 means 50%. Defaults to 100%.
 */
+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double)rate;

/**
 *@brief Start the Tingyun SDK; when immediately is NO, do not connect to the server or send requests yet.
 *@param appId Unique App ID from the Tingyun platform.
 *@param immediately Whether to connect to the Tingyun server immediately. Defaults to YES; use with + (void)setUserPrivacyAgreement:(BOOL)agreement.
 */
+(void)startWithAppID:(NSString*)appId launchImmediately:(BOOL)immediately;

/**
 *@brief Specify launch probability and channel ID.
 *@param rate Launch probability between 0 and 1; 0.5 means 50%. Defaults to 100%.
 *@param useBuildVersion YES to prefer CFBundleVersion; NO to use CFBundleShortVersionString. Default NO.
 *@param channelId Distribution channel ID.
 */
+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double) rate channelId:(NSString *)channelId useBuildVersion:(BOOL)useBuildVersion;

/**
 *@brief Specify launch probability, channel ID, and immediate connect option.
 *@param rate Launch probability between 0 and 1; 0.5 means 50%. Defaults to 100%.
 *@param useBuildVersion YES to prefer CFBundleVersion; NO to use CFBundleShortVersionString. Default NO.
 *@param channelId Distribution channel ID.
 *@param immediately Whether to connect to the Tingyun server immediately. Defaults to YES.
 */
+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double) rate channelId:(NSString *)channelId useBuildVersion:(BOOL)useBuildVersion launchImmediately:(BOOL)immediately;

/**
 *@brief Enable embedded console logging; disabled by default.
 */
+ (void)setLogEnable:(BOOL)enale __attribute__((deprecated("please use +setLogLevel:")));

/**
 *@brief Set embedded console log level; disabled by default. Recommended: NBSLogLevelInfo.
 */
+ (void)setLogLevel:(NBSSDKLogLevel)logLevel;

/**
 *@brief Ignore certain network requests. Requests for which the block returns true are skipped.
 */
+(void)setIgnoreBlock:(BOOL (^)(NSURLRequest* request)) block;

/**
 *@brief setCustomerData:forKey: adds context info that will be sent on crash to help analysis. Can be called multiple times anywhere.
 */
+(void)setCustomerData:(NSString*)data forKey:(NSString*)key __attribute__((deprecated("please use +setGlobalContext:forKey:")));

/**
 * @brief Set global context info shown in crash, ANR, and UX details.
 */
+(void)setGlobalContext:(NSString *)value forKey:(NSString *)key;

/**
 *@brief Configure modules for the first launch; call before other methods. By default only Crash is on before communicating with Tingyun. Enable Net/UI to collect first-launch data.
 * Example to collect crash and first-launch data:
 * [NBSAppAgent setStartOption:NBSOption_Net|NBSOption_Crash|NBSOption_UI]
 *@note First launch options are not controlled by Tingyun switches.
 */
+(void)setStartOption:(int)option;

/**
 *@brief Leave a breadcrumb. Added info is collected in order and sent with crash data.
 *@param breadcrumb Custom info text.
*/
+(void)leaveBreadcrumb:(NSString *)breadcrumb;

/**
 *@brief Set user identifier, up to 256 characters.
 *@param userId Unique user identifier.
 *@note For data accuracy, set this only once.
 */
+(void)setUserIdentifier:(NSString *)userId;

/**
 *@brief Get current user identifier.
 */
+ (NSString *)getUserIdentifier;

/**
 *@brief Set the request header key used to mark a request ID.
 */
+(void)setRequestIDHeaderKey:(NSString *)key;

/**
 *@brief Custom event.
 *@param eventID Up to 32 characters; letters, numbers, underscore; no spaces or escape characters.
 *@param eventTag Event tag.
 *@param eventProperties Additional properties; dictionary; more than 30 key-value pairs ignored; values support String/Number; may be nil.
 */
+ (void)trackEvent:(NSString *)eventID withEventTag:(NSString *)eventTag withEventProperties:(NSDictionary *)eventProperties  __attribute__((deprecated("please use +reportEvent:properties:")));

/**
 *Configure which signals to ignore.
 *Supported signals: SIGABRT(6), SIGBUS(10), SIGFPE(8), SIGILL(4), SIGSEGV(11), SIGSYS(12), SIGTRAP(5), SIGKILL(9)
 *Parameter can be NSString/NSNumber/NSArray.
 *Examples:
 *[NBSAppAgent ignoreSomeSignalCrash:@"SIGABRT"];
 *[NBSAppAgent ignoreSomeSignalCrash:@6];
 *[NBSAppAgent ignoreSomeSignalCrash:@[@6,@10]];
 *[NBSAppAgent ignoreSomeSignalCrash:@[@"SIGABRT",@"SIGBUS"]];
 */
+ (void)ignoreSomeSignalCrash:(id)ignore;

/**
 *@brief Report custom error: message max 1024 bytes; metaData values support NSNumber/NSString/NSArray/NSDictionary; max 128 KB.
 */
+ (void)reportError:(NSString *)message withMetaData:(NSDictionary *)metaData;
+ (void)reportError:(NSString *)message withException:(NSException *)exception withMetaData:(NSDictionary *)metaData;
+ (void)reportError:(NSString *)message withContext:(NSDictionary *)dictionary;
/**
 *@brief Return whether Tingyun App is started.
 */
+ (BOOL)tingyunAppIsStart;

/**
 *@brief Enable encryption.
 *@param need YES encrypts uploaded data; default NO.
 *@note When YES, include the Tingyun SM dynamic library or uploads may fail.
 */
+ (void)encryptionRequired:(BOOL)need;

/**
 *@brief React Native bridge helpers.
 */
+ (void)enterAction:(NSString *)name withKey:(NSNumber *)key withTime:(NSString *)time;
+ (void)leaveAction:(NSNumber *)key withTime:(NSString *)time;

/**
 *@brief Whether to customize the end point of launch; call before starting the SDK.
 */
+ (void)customLaunchEnd:(BOOL)enable;

/**
 *@brief Custom launch end marker; call when launch finishes.
 */
+ (void)launchFinish:(NSString *)lanuchName;

/**
 *@brief Mark custom action start.
 */
+ (void)customActionStart:(NSString *)actionName;

/**
 *@brief Mark custom action end.
 */
+ (void)customActionEnd:(NSString *)actionName withTag:(NSString *)tag withCustomInfo:(NSDictionary <NSString*, NSString*>*)customInfo;

/**
 *@return Device ID generated by Tingyun platform; may be empty on first fetch.
 */
+ (NSString *)getTingyunDeviceId;

/**
 *@brief Set callback when SDK captures specific errors.
 *@param handler Callback invoked on error.
 */
+ (void)setAgentErrorEventFeedBack:(void(^)(NBSErrorEventType feedBack, NSString *errorId))handler;

/**
 *@brief Configure errorId generation rule used by setAgentErrorEventFeedBack:. Defaults to timestamp(ms)+6-digit random.
 */
+ (void)setErrorIdGenerateBlock:(NSString* (^)(void))block;

/**
 *@brief Set custom App version name, up to 64 characters; letters/numbers/underscore; call before SDK start.
 */
+ (void)setVersionName:(NSString *)versionName;

/**
 *@brief Set current business line; same key overwrites previous value.
 *@params businessLine Business name, max 256 bytes.
 *@params key Reserved for Tingyun internal use; obtain values from Tingyun.
 */
+ (void)setBusinessLine:(NSString *)businessLine forKey:(NSString *)key;

/**
 *@brief Set custom callback for crash or ANR.
 */
+ (void)setCallBack:(NBSCallBack)callback withType:(NBSCallBackType)type;

/**
 *@brief Create a transaction span.
 *@param name Transaction name, e.g., a specific gRPC method; required; max 1024 characters (truncated if longer).
 *@param operation Transaction type, e.g., grpc; required; max 128 characters (truncated if longer).
 *@return Transaction span.
 */
+ (id<NBSSpan>)startTransactionWithName:(NSString *)name operation:(NSString *)operation;

/**
 *@brief Create an independent span.
 *@param name Span name; required; max 1024 characters (truncated if longer).
 *@param operation Operation name for the span, e.g., websocket; required; max 128 characters (truncated if longer).
 */
+ (id<NBSSpan>)startSpanWithName:(NSString *)name operation:(NSString *)operation;

/**
 *@brief Notify SDK whether the user agreed to the privacy policy.
 *@param agreement YES marks local consent (removed when app uninstalled).
 *@discussion When using +startWithAppID:launchImmediately: with immediately NO, SDK checks local consent; if absent it only collects data until agreement becomes YES.
 */
+ (void)setUserPrivacyAgreement:(BOOL)agreement;

/**
 *@brief Set latitude/longitude. SDK does not auto-collect location for compliance.
 */
+ (void)setLatitude:(double)latitude longitude:(double)longitude;

/*
 *@brief Set encryption key; if not set, SDK generates a fixed default.
 *@param key Key length must be 16/24/32 bytes; max 32 bytes.
 *@note Call before SDK init; call every launch with the same key, otherwise decryption may fail.
 */
+ (void)setEncryptKey:(NSString *)key;

/**
 *@brief Start a new session and end the previous one; called by +startWithAppID: by default.
 *@note Call only after SDK init; generally not needed unless customizing session boundaries.
 */
+ (void)startNextSession;

/**
 *@brief Get current sessionId.
 */
+ (NSString *)getSessionId;

/**
 *@brief Set idle timeout for a session. Default 600s; 0 disables idle timeout (session ends only on exit or startNextSession). Call before SDK init; only first set takes effect. Units: seconds.
 *@param idleTime Minimum 60 seconds.
 */
+ (void)setSessionIdleTime:(NSUInteger)idleTime;

/**
 *@brief Report custom event.
 *@param name Event name; required; max 1024 characters (truncated if longer).
 *@param properties Event properties.
 */
+ (void)reportEvent:(NSString *)name properties:(NSDictionary <NSString*,NSString*>*)properties;

/**
 *@brief Get SDK version.
 */
+ (NSString *)agentVersion;

/**
 *@brief Do not collect crash/ANR on jailbroken devices; call before SDK start.
 */
+ (void)disableJailbreakExceptionDataCollection;

/**
 *@brief Add local task to diagnosis module; when scene triggers, tasks matching condition auto-execute.
 */
+ (void)addDiagnosisTask:(NBSDiagnosisTask *)task;

/**
 *@brief Queue a diagnosis task for async execution; ignores task.condition.
 */
+ (void)startDiagnosisTask:(NBSDiagnosisTask *)task;

/**
 * Disable SDK; takes effect next launch; uploads stop immediately.
 */
+ (void)disable;

/**
 * @brief Disable SDK for a limited time.
 * @param unit Time unit.
 * @param duration Duration.
 */
+ (void)disableTimeUnit:(NBSTimeUnit)unit duration:(NSInteger)duration;

/**
 * Enable SDK; takes effect next launch.
 */
+ (void)enable;

/**
 *@brief Enable IMSecurity SDK request monitoring; off by default.
 *@note Tingyun intercepts IMSecurity request APIs to collect performance data. If those APIs change, interception may fail or crash. Test after enabling or upgrading IMSecurity.
 */
+ (void)startIMSecurityMonitor;

/**
 *Enable capturing request content.
 */
+ (void)enableNetworkContentRecord;

/**
 *Configure custom request header/body capture.
 */
+ (void)setupRequestSanitizer:(void (^)(NBSRequestSanitizer *requestSanitizer))configureSanitizer;

/**
 *Configure custom response header/body capture.
 */
+ (void)setupReponseSanitizer:(void (^)(NBSResponseSanitizer *responseSanitizer))configureSanitizer;

/**
 *@brief Set network response time threshold in ms.
 *@param threshold Threshold in ms.
 */
+ (void)setNetworkThreshold:(NSInteger)threshold;

/**
 *@brief Set ANR duration threshold; default 1 minute.
 *@param threshold Threshold in ms.
 */
+ (void)setAnrThreshold:(NSInteger)threshold;
#pragma mark - Video Plugin APIs
/**
 * Start video replay.
 */
+ (void)startVideoReplay;

/**
 * Pause; effective only when recording.
 */
+ (void)pauseVideoReplay;

/**
 * Resume; effective only when paused.
 */
+ (void)resumeVideoReplay;

/**
 *@brief Mask sensitive view content.
 *@param view View to mask.
 */
+(void)maskSensitiveView:(UIView *)view;

/**
 *@brief Unmask sensitive view content.
 *@param view View to unmask.
 */
+(void)unmaskSensitiveView:(UIView *)view;

/**
 *@brief Mask sensitive region relative to main window.
 *@param region Region to mask.
 */
+(void)maskSensitiveRegion:(CGRect)region;

/**
 *@brief Unmask sensitive region relative to main window.
 *@param region Region to unmask.
 */
+(void)unmaskSensitiveRegion:(CGRect)region;

/**
 *@brief Mask sensitive view by accessibilityIdentifier; identifier must be set beforehand.
 */
+ (void)maskViewId:(NSString*)viewId;

/**
 *@brief Mask sensitive screens; pass VC class names.
 */
+ (void)maskScreens:(NSArray <NSString *>*)screens;

/**
 *@brief Mask sensitive classes; pass VC or view class names.
 */
+ (void)maskClasses:(NSArray <NSString *>*)classes;

#pragma mark - Page Load APIs
/**
 *@brief Enable custom page end marker.
 *@param enable Whether to customize.
 *@result identifier For matching finish.
 */
+ (NSInteger)customPageLoad:(BOOL)enable;

/**
 * @brief Mark custom page finished.
 * @param customId ID returned by customPageLoad.
 * @param pageName Page name.
 */
+ (void)customPageLoadFinish:(NSInteger)customId withPageName:(NSString *)pageName;

/**
 *Set page load scan interval in ms; default 50ms.
 */
+ (void)setPageScanInterval:(NSInteger)interval;

/**
 *Set page load timeout in seconds; default 5s; max 15s.
 */
+ (void)setPageLoadTimeoutSec:(NSInteger)sec;

/**
 *Enable 8060 algorithm for page timing.
 */
+ (void)enableNewCalcAlgoForPage;

#pragma mark - Custom Pages

/**
 *@param pageName Custom page name; max 128 characters.
 *@return pageId Page ID.
 */
+ (NSString *)startPageWithName:(NSString *)pageName;

/**
 *@param pageName Custom page name; max 128 characters.
 *@return pageId Page ID.
 */
+ (NSString *)finishPageWithName:(NSString *)pageName;

#pragma mark - For Tags
/**
 *@brief Set global tags attached to every record; same key overwrites. Can be set anywhere.
 *@param key Up to 32 characters; starts with letter; letters/numbers/underscore only; invalid data dropped.
 *@param value Up to 200 characters; longer data dropped.
 */
+ (void)setTagValue:(NSString  *)value forKey:(NSString *)key;
/**
 *@brief Remove tag for key.
 */
+ (void)removeTagForKey:(NSString *)key;
/**
 * @brief Clear all tags.
 */
+ (void)clearTags;
/**
 *@brief Return tag value for key.
 */
+ (NSString *)tagForKey:(NSString *)key;
/**
 *@brief Get current tags.
 */
+ (NSDictionary *)getTags;

@end

/*
 Example 1: simplest
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 
 Example 2: sample rate 50%
 [NBSAppAgent startWithAppID:@"xxxxxxx" rateOfLaunch:0.5f];
 
 Example 3: ignore URLs containing 127.0.0.1
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 [NBSAppAgent setIgnoreBlock:^BOOL(NSURLRequest* request)
 {
 return [request.URL.absoluteString rangeOfString:@"127.0.0.1"].location!=NSNotFound;//ignore URLs containing 127.0.0.1
 }
 ];
 
 Example 4: start SDK with options:
 [NBSAppAgent setStartOption:NBSOption_Net|NBSOption_Crash];//enable only network and crash monitoring; disable UI monitoring
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 */

#pragma mark Only for Enterprise-Edition:
@interface NBSAppAgent (Enterprise)

///@brief Set redirect URL.
+(void)setRedirectURL:(NSString *)url;

///@brief Set multiple redirect URLs to avoid DNS hijack; use when you have backups.
///@note Do not use together with setRedirectURL:; choose one approach.
+(void)setMultiRedirectUrls:(NSArray *)urlArray;

///@brief Allow HTTP (not HTTPS) when connecting to DC; YES uses HTTP; default NO.
+(void)setHttpEnabled:(BOOL)isEnable;

///@brief Customize certificate validation for upload endpoints.
+ (void)setAuthenticationChallengeHandler:(void (^)(NSURLSession *session, NSURLSessionTask *task, NSURLAuthenticationChallenge *challenge, void (^completionHandler)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential)))authenticationChallengeHandler;
@end

@interface UIView (NBSUIProperties)

/// viewID
@property (nonatomic, copy) NSString *tingyunAttributesIdentifier;
/// view alias
@property (nonatomic, copy) NSString *tingyunAttributesName;
/// Do not collect data for this view
@property (nonatomic, assign) BOOL tingyunAttributesShouldIgnored;

@end
/// Page load helper to fine-tune page completion detection
@interface UIView (NBSPageLoadAssistant)
/// Mark view invalid until content rendered, avoiding placeholder skewing page completion
@property (nonatomic, assign) BOOL isInvalidView;
/// Ignore this view when computing page completion
@property (nonatomic, assign) BOOL isIgnoredView;

@end

@interface UIViewController (NBSUIProperties)

/// VC alias
@property (nonatomic, copy) NSString *tingyunAttributesPageName;

/// Ignore this VC; do not collect its data
@property (nonatomic, assign) BOOL tingyunAttributesShouldIgnored;

@end

