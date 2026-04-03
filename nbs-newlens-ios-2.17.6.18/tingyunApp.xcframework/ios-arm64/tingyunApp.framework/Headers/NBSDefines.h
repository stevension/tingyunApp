//
//  NBSDefines.h
//  NBSAppAgent
//
//  Created by tgf on 2021/11/22.
//

#ifndef NBSDefines_h
#define NBSDefines_h

typedef NS_ENUM(NSInteger, NBSOPTION)
{
    NBSOption_Net           = 1<<0,
    NBSOption_UI            = 1<<1,
    NBSOption_Crash         = 1<<2,
    NBSOPTION_LOG           = 1<<12,
};

typedef NS_ENUM(NSInteger, NBSErrorEventType)
{
    NBSErrorEventCrash,
    NBSErrorEventANR,
    NBSErrorEventCustomError,
    NBSErrorEventNetworkError,
};

typedef NS_OPTIONS(NSInteger,NBSSDKLogLevel){
    NBSSDKLogLevelNone  = 0,
    NBSSDKLogLevelDebug = 1 ,
    NBSSDKLogLevelInfo  = 2,
    NBSSDKLogLevelWarning = 3,
    NBSSDKLogLevelError = 4,
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
    NBSSpanMetricUnitBit = 0,///bit
    NBSSpanMetricUnitByte,///byte
    NBSSpanMetricUnitKilobytes,///KB
    NBSSpanMetricUnitMegabytes,///MB
    NBSSpanMetricUnitMillisecond,///millisecond
    NBSSpanMetricUnitSecond,///second
    NBSSpanMetricUnitMinute,///minute
    NBSSpanMetricUnitHour,///hour
    NBSSpanMetricUnitDay,///day
    NBSSpanMetricUnitBitps,///bit/second
    NBSSpanMetricUnitByteps,///byte/second
    NBSSpanMetricUnitKbps,///kilobyte/second
    NBSSpanMetricUnitMbps,///megabyte/second
};

/**
 * Convert NBSSpanMetricUnit enum to string.
 */
static NSString * const NBSSpanMetricUnitNames[] = {
    @"b",///bit
    @"B",///byte
    @"KB",///kilobyte
    @"MB",///megabyte
    @"ms",///millisecond
    @"s",///second
    @"m",///minute
    @"h",///hour
    @"d",///day
    @"b/s",///bit/second
    @"B/s",///byte/second
    @"KB/s",///kilobyte/second
    @"MB/s"///megabyte/second
};

typedef NS_ENUM(NSInteger, NBSDiagnosisTaskType)
{
    NBSDiagnosisTaskTCPPing,
    NBSDiagnosisTaskICMPPing,
    NBSDiagnosisTaskMTR,
    NBSDiagnosisTaskDownload
};

typedef NS_ENUM(NSInteger, NBSDiagnosisTaskScene)
{
    NBSDiagnosisTaskSceneAfterNetFinished = 1,//run after network request completes
    NBSDiagnosisTaskSceneAfterNetError,//run after network request error
    NBSDiagnosisTaskSceneUnknown,//unknown; internal use only, do not set
};

typedef NS_ENUM(NSInteger, NBSTimeUnit) {
    NBSTimeUnitSecond = 0,///second
    NBSTimeUnitMinute,///minute
    NBSTimeUnitHour,///hour
    NBSTimeUnitDay,///day
};

typedef NS_ENUM(NSInteger, NBSPrivacyDataType){
    NBSPrivacyDataDeviceType,///device type, e.g., phone/Pad
    NBSPrivacyDataManufacturer,///manufacturer, e.g., Apple
    NBSPrivacyDataManufacturerModel,///device model, e.g., iphone10,1
    NBSPrivacyDataOSVersion,///OS version
    NBSPrivacyDataDeviceSize,///device size, e.g., 0-unknown 1–Small
    NBSPrivacyDataBundleId,///App bundle Id
    NBSPrivacyDataAppName,///App name
    NBSPrivacyDataAppVersion,///App version
    NBSPrivacyDataCarrierCode,///carrier code, e.g., 46000
    NBSPrivacyDataConnectType,///network connection type, e.g., WiFi, 5g
    NBSPrivacyDataNetType,///network type, e.g., GPRS
    NBSPrivacyDataNone,///clear blacklist setting; cannot combine with other values
};

typedef void(^NBSCallBack)(NSDictionary *context);

void nbsCustomerAPI_logStart(NSString *eventName,id self,SEL _cmd);
void nbsCustomerAPI_logFinish(NSString *eventName,SEL _cmd);
/*
 Custom API:
 @str_eventName: may be nil; nil defaults to the current method name.
 Warning:
 1) Must instrument on the same thread; do not cross threads.
 2) Must instrument within the same method; do not cross methods.
 3) Do not use in asynchronous loading.
 4) Do not use in recursive calls.
 Please follow the above to avoid inaccurate data!
 For example:
 - (void)doSomething
 {
 beginTracer(@"doSomething")
 
 //write your code here
 
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
