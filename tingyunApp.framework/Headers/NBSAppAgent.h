//
//  NBSAppAgent.h
//
//  Created by yang kai on 14-3-12.
//  Copyright (c) 2014年 NBS. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, NBSOPTION)
{
    NBSOption_Net           = 1<<0,
    NBSOption_UI            = 1<<1,
    NBSOption_Crash         = 1<<2,
};
typedef NS_ENUM(NSInteger, NBSErrorEventType)
{
    NBSErrorEventCrash,
    NBSErrorEventANR,
    NBSErrorEventCustomError,
};
typedef NS_ENUM(NSInteger, NBSCallBackType)
{
    NBSCallBackOnCrash          = 1<<0,
    NBSCallBackOnANR            = 1<<1,
};
typedef void(^NBSCallBack)(NSDictionary *context);

void nbsCustomerAPI_logStart(NSString *eventName,id self,SEL _cmd);
void nbsCustomerAPI_logFinish(NSString *eventName,SEL _cmd);
/*
 自定义API：
 @str_eventName:可为nil，如果设置为nil，则默认为当前方法名
 warning：
 1、自定义API接口只能在同一线程中进行动态埋点，不可跨线程操作
 2、自定义API接口只能在同一方法内进行动态埋点，不可跨方法操作
 3、自定义API接口不能在异步加载中使用
 4、自定义API接口不能在递归调用中使用
 请务必遵守以上几点，否则可能导致数据不准确！
 For example：
 - (void)doSomething
 {
 beginTracer(@"doSomething")
 
 //write you code here
 
 endTracer(@"doSomething")
 }
 */

#define beginTracer(str_eventName) {\
    nbsCustomerAPI_logStart(str_eventName,self,_cmd);\
}
#define endTracer(str_eventName) {\
   nbsCustomerAPI_logFinish(str_eventName,_cmd);\
}

@interface NBSAppAgent : NSObject
/**
 启动NBSAppAgent。一般，只需本函数足矣！
 */
+(void)startWithAppID:(NSString*)appId;
/**
 @channelID:渠道ID,默认为AppStore
 */
+(void)startWithAppID:(NSString *)appId channelId:(NSString *)channelId;
/**
 rate指定了启动的概率，应该是0～1之间的一个数，0.5表示一半概率。默认100%
 */
+(void)startWithAppID:(NSString*)appId rateOfLaunch:(double) rate;
/*
 locationAllowed指明是否使用位置服务，默认是不使用。
 */
+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed;
/**
 同时指定启动概率、渠道ID
 useBuildVersion：YES优先使用CFBundleVersion版本号，NO使用CFBundleShortVersionString，默认为NO。
 */
+(void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed rateOfLaunch:(double) rate channelId:(NSString *)channelId useBuildVersion:(BOOL)useBuildVersion;

/**
 是否打开嵌码日志，默认关闭。
 */
+ (void)setLogEnable:(BOOL)enale;

/**
 忽略某些网络请求。block返回true的，都被忽略。
 */
+(void)setIgnoreBlock:(BOOL (^)(NSURLRequest* request)) block;
/**
 setCustomerData:forKey:的目的是这样的：通过这个方法设置的信息，会在crash时作为环境信息提交，帮助用户分析问题。此函数可以在任何地方多次调用
 */
+(void)setCustomerData:(NSString*)data forKey:(NSString*)key;
/**
 设置首次启动选项，SDK有几个功能，借此可以关闭某个。此函数应该在其他函数之前调用。
 SDK首次初始化由于尚未与听云平台交互，默认模块开关仅开启「崩溃模块」，可以通过开启「网络模块」和「UI模块」采集应用首次启动数据。
 例如采集崩溃和首次启动数据：
 [NBSAppAgent setStartOption:NBSOption_Net|NBSOption_Crash|NBSOption_UI]
 @warning:调用该接口设置启动选项，SDK首次启动不受听云平台开关控制
 */
+(void)setStartOption:(int)option;
/**
 面包屑功能：是指用户在程序中通过该接口添加的一些信息,当程序发生崩溃时，将会把这些添加的信息，按顺序收集起来，和崩溃信息都发送给服务器
 @breadcrumb:自定义信息
*/
+(void)leaveBreadcrumb:(NSString *)breadcrumb;
/**
 设置用户标识符,不能超过256个字符
 @userId:能唯一标识一个用户的信息
 warning:为保证数据的准确性，该接口最好只设置一次
 */
+(void)setUserIdentifier:(NSString *)userId;

/**
 指定请求头中标识一次请求的key
 */
+(void)setRequestIDHeaderKey:(NSString *)key;

/**
 自定义事件：
 eventID 最多包含32个字符，支持中文、英文、数字、下划线，但不能包含空格或其他的转义字符
 eventTag 事件标签
 eventProperties 其它附加属性，字典，超过30个键值对无效，可以为nil。Value值仅支持字符串（String）和数字（Number）类型
 */
+ (void)trackEvent:(NSString *)eventID withEventTag:(NSString *)eventTag withEventProperties:(NSDictionary *)eventProperties;

/**
 设置SDK忽略某些类型的信号。
 SDK支持采集的信号
 SIGABRT, //6
 SIGBUS,  //10
 SIGFPE,  //8
 SIGILL,  //4
 SIGSEGV, //11
 SIGSYS,  //12
 SIGTRAP, //5
 参数支持字符串、NSNumber、NSArray
 例：
 [NBSAppAgent ignoreSomeSignalCrash:@"SIGABRT"];
 [NBSAppAgent ignoreSomeSignalCrash:@6];
 [NBSAppAgent ignoreSomeSignalCrash:@[@6,@10]];
 [NBSAppAgent ignoreSomeSignalCrash:@[@"SIGABRT",@"SIGBUS"]];
 */
+ (void)ignoreSomeSignalCrash:(id)ignore;

/**
 自定义错误：message 长度最大1024字节  metaData的value值支持 NSNumber,NSString,NSArray，NSDictionary类型，最大128k。
 */
+ (void)reportError:(NSString *)message withMetaData:(NSDictionary *)metaData;
+ (void)reportError:(NSString *)message withException:(NSException *)exception withMetaData:(NSDictionary *)metaData;

/**
 返回一个BOOL值，代表tingyunApp是否启动
 */
+ (BOOL)tingyunAppIsStart;

/**
 关闭更新提示log。
 SDKVersion为最新的SDK版本
 */
+ (void)closeLogForUpdateHint:(NSString *)SDKVersion;

/**
 @brief use for react-native
 */
+ (void)enterAction:(NSString *)name withKey:(NSNumber *)key withTime:(NSString *)time;
+ (void)leaveAction:(NSNumber *)key withTime:(NSString *)time;

/**
 @brief 是否自定义启动的结束点，在启动SDK之前调用。
 */
+ (void)customLanuchEnd:(BOOL)enable;
/**
 @brief 自定义结束时间点，在启动结束时调用。
 */
+ (void)lanuchFinish:(NSString *)lanuchName;

/**
 @brief 自定义操作开始。
 */
+ (void)customActionStart:(NSString *)actionName;
/**
 @brief 自定义操作结束
 */
+ (void)customActionEnd:(NSString *)actionName withTag:(NSString *)tag withCustomInfo:(NSDictionary *)customInfo;

/**
 @return 返回听云平台生成的设备id，该id为服务端返回，首次获取可能为空
 */
+ (NSString *)getTingyunDeviceId;

/**
 @brief 设置SDK捕获到特定异常时的回调
 @param handler 异常发生时的回调
 */
+ (void)setAgentErrorEventFeedBack:(void(^)(NBSErrorEventType feedBack, NSString *uuid))handler;

/**
 @brief 设置自定义App版本号，最多包含64个字符，支持中文、英文、数字、下划线
 */
+ (void)setVersionName:(NSString *)versionName;
/**
@brief 设置当前业务，相同的key值会覆盖，保留最新值
 @params businessLine 业务名称，最大长度为256字节
 @params key 供听云内部业务使用，取值请咨询听云平台
 */
+ (void)setBusinessLine:(NSString *)businessLine forKey:(NSString *)key;

/**
 *是否自定义页面结束点
 *@param enable 是否自定义.
 *@result identifier 关联结束。
 */
+ (NSInteger)customPageLoad:(BOOL)enable;

/**
 *自定义页面结束。
 *@param customId 传入customPageLoad返回的id。
 *@param pageName 页面名称
 */
+ (void)customPageLoadFinish:(NSInteger)customId withPageName:(NSString *)pageName;
/**
 @brief 当发生crash或者卡顿时设置自定义回调
 */
+ (void)setCallBack:(NBSCallBack)callback withType:(NBSCallBackType)type;

@end

/*
 Example 1:最简单的
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 
 Example 2:指定采样率 50%
 [NBSAppAgent startWithAppID:@"xxxxxxx" rateOfLaunch:0.5f];
 
 Example 3:忽略包含127.0.0.1的url
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 [NBSAppAgent setIgnoreBlock:^BOOL(NSURLRequest* request)
 {
 return [request.URL.absoluteString rangeOfString:@"127.0.0.1"].location!=NSNotFound;//忽略包含127.0.0.1的url
 }
 ];
 
 Example 4:使用选项启动SDK：
 [NBSAppAgent setStartOption:NBSOption_Net|NBSOption_Crash];//只开启网络和崩溃的监控，不开启UI的监控
 [NBSAppAgent startWithAppID:@"xxxxxxx"];
 */

#pragma mark Only for Enterprise-Edition:
@interface NBSAppAgent (Enterprise)
///@brief 设置转向url
+(void)setRedirectURL:(NSString *)url;
///@brief 设置多个转向的url，若有多个转向地址可以使用此接口，目的是为了防止当某个转向url发生dns劫持时，有其他地址可以备用
///@note  不可与接口setRedirectURL:同时调用，二选一即可
+(void)setMultiRedirectUrls:(NSArray *)urlArray;
///@brief 链接dc允许http而非https，YES为使用Http，默认为NO
+(void)setHttpEnabled:(BOOL)isEnable;
///@brief 自定义上传数据接口的证书校验策略。
+ (void)setAuthenticationChallengeHandler:(void (^)(NSURLSession *session, NSURLSessionTask *task, NSURLAuthenticationChallenge *challenge, void (^completionHandler)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential *credential)))authenticationChallengeHandler;


@end



