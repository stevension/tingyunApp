//
//  NBSDefines.h
//  NBSAppAgent
//
//  Created by 唐桂帆 on 2021/11/22.
//

#ifndef NBSDefines_h
#define NBSDefines_h

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
    NBSErrorEventNetworkError,
};

typedef NS_ENUM(NSInteger, NBSCallBackType)
{
    NBSCallBackOnCrash          = 1<<0,
    NBSCallBackOnANR            = 1<<1,
};

typedef NS_ENUM(NSInteger, NBSSpanStatus) {
    NBSSpanStatusUndefined = 0,
    NBSSpanStatusSuccess = 1,
    NBSSpanStatusFailed = -1,
};

typedef NS_ENUM(NSInteger, NBSSpanMetricUnit) {
    NBSSpanMetricUnitBit = 0,///比特
    NBSSpanMetricUnitByte,///字节
    NBSSpanMetricUnitKilobytes,///KB
    NBSSpanMetricUnitMegabytes,///MB
    NBSSpanMetricUnitMillisecond,///毫秒
    NBSSpanMetricUnitSecond,///秒
    NBSSpanMetricUnitMinute,///分钟
    NBSSpanMetricUnitHour,///小时
    NBSSpanMetricUnitDay,///天
    NBSSpanMetricUnitBitps,///比特/秒
    NBSSpanMetricUnitByteps,///字节/秒
    NBSSpanMetricUnitKbps,///千字节/秒
    NBSSpanMetricUnitMbps,///兆字节/秒
};

/**
 * 将枚举NBSSpanMetricUnit转换为字符串
 */
static NSString * const NBSSpanMetricUnitNames[] = {
    @"b",///比特
    @"B",///字节
    @"KB",///千字节
    @"MB",///兆字节
    @"ms",///毫秒
    @"s",///秒
    @"m",///分
    @"h",///小时
    @"d",///天
    @"b/s",///比特/秒
    @"B/s",///字节/秒
    @"KB/s",///千字节/秒
    @"MB/s"///兆字节/秒
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

#define NBS_NO_INIT                                                                             \
    -(instancetype)init NS_UNAVAILABLE;                                                            \
    +(instancetype) new NS_UNAVAILABLE;

#endif /* NBSDefines_h */
