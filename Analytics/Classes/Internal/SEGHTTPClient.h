#import <Foundation/Foundation.h>
#import "SEGAnalytics.h"

// TODO: Make this configurable via SEGAnalyticsConfiguration
// NOTE: `/` at the end kind of screws things up. So don't use it
//#define SEGMENT_API_BASE [NSURL URLWithString:@"https://api-segment-io-5fsaj1xnikhp.runscope.net/v1"]
//#define SEGMENT_CDN_BASE [NSURL URLWithString:@"https://cdn-segment-com-5fsaj1xnikhp.runscope.net/v1"]
//#define MOBILE_SERVICE_BASE [NSURL URLWithString:@"https://mobile--service-segment-com-5fsaj1xnikhp.runscope.net/v1"]
#define SEGMENT_API_BASE [NSURL URLWithString:@"https://api.segment.io/v1"]
#define SEGMENT_CDN_BASE [NSURL URLWithString:@"https://cdn.segment.com/v1"]
#define MOBILE_SERVICE_BASE [NSURL URLWithString:@"https://mobile-service.segment.com/v1"]


@interface SEGHTTPClient : NSObject

@property (nonatomic, strong) SEGRequestFactory requestFactory;

+ (SEGRequestFactory)defaultRequestFactory;
+ (NSString *)authorizationHeader:(NSString *)writeKey;

- (instancetype)initWithRequestFactory:(SEGRequestFactory)requestFactory;

/**
 * Upload dictionary formatted as per https://segment.com/docs/sources/server/http/#batch.
 * This method will convert the dictionary to json, gzip it and upload the data.
 * It will respond with retry = YES if the batch should be reuploaded at a later time.
 * It will ask to retry for json errors and 3xx/5xx codes, and not retry for 2xx/4xx response codes.
 */
- (NSURLSessionUploadTask *)upload:(NSDictionary *)batch forWriteKey:(NSString *)writeKey completionHandler:(void (^)(BOOL retry))completionHandler;

- (NSURLSessionDataTask *)settingsForWriteKey:(NSString *)writeKey completionHandler:(void (^)(BOOL success, NSDictionary *settings))completionHandler;

- (NSURLSessionDataTask *)attributionWithWriteKey:(NSString *)writeKey forDevice:(NSDictionary *)context completionHandler:(void (^)(BOOL success, NSDictionary *properties))completionHandler;

@end
