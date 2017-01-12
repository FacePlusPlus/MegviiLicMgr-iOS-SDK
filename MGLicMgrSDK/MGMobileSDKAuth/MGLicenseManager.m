//
//  MGLicenseManager.m
//  MGBaseKit
//
//  Created by 张英堂 on 16/9/5.
//  Copyright © 2016年 megvii. All rights reserved.
//

#import "MGLicenseManager.h"
#import "MG_Common.h"
#import "MG_LicenseManager.h"

@implementation MGLicenseManager

+ (NSString*)getContextWithDuration:(MGLicenseDuration)duration
                               UUID:(NSString *)UUID
                          candidate:(NSArray <NSNumber *>*)APIName{
    const char *uuidChar =  [UUID cStringUsingEncoding:NSUTF8StringEncoding];
    
    int32_t stringLength = 0;
    const char* contextData = NULL;
    
    MG_RETCODE contextCode = MG_RETCODE_FAILED;
    
    if (APIName.count == 0){
    }else if (APIName.count == 1) {
        contextCode = mg_licmgr.GetContext(MG_LICMGR_DURATION_30DAYS, uuidChar, &contextData, &stringLength, [APIName[0] integerValue],MG_END_ARG);
    }else if (APIName.count == 2){
        contextCode = mg_licmgr.GetContext(MG_LICMGR_DURATION_30DAYS, uuidChar, &contextData, &stringLength, [APIName[0] integerValue],[APIName[1] integerValue],MG_END_ARG);
    }else if (APIName.count == 3){
        contextCode = mg_licmgr.GetContext(MG_LICMGR_DURATION_30DAYS, uuidChar, &contextData, &stringLength, [APIName[0] integerValue],[APIName[1] integerValue],[APIName[2] integerValue],MG_END_ARG);
    }else if (APIName.count == 4){
        contextCode = mg_licmgr.GetContext(MG_LICMGR_DURATION_30DAYS, uuidChar, &contextData, &stringLength, [APIName[0] integerValue],[APIName[1] integerValue],[APIName[2] integerValue],[APIName[3] integerValue],MG_END_ARG);
    }
    
    if (contextCode != MG_RETCODE_OK) {
        return nil;
    }
    NSString *contextString = [NSString stringWithCString:contextData encoding:NSUTF8StringEncoding];

    return contextString;
}

+ (BOOL)setLicense:(NSString*) license{
    
    MG_RETCODE contextCode = MG_RETCODE_FAILED;

    const char *tempStr =  [license cStringUsingEncoding:NSUTF8StringEncoding];
    if (tempStr) {
      contextCode = mg_licmgr.SetLicence(tempStr, (int32_t)license.length);
    }
    if (contextCode == MG_RETCODE_OK) {
        return YES;
    }
    return NO;
}

+ (NSURLSessionTask *)takeLicenseFromNetwokrDuration:(MGLicenseDuration)duration
                                  UUID:(NSString *)UUID
                             candidate:(NSArray <NSNumber *>*)APIName
                                apiKey:(NSString *)apiKey
                             apiSecret:(NSString *)apiSecret
                                finish:(void(^)(bool License, NSError *error))finish{
    
    NSString *contextString = [MGLicenseManager getContextWithDuration:duration
                                                                  UUID:UUID
                                                             candidate:APIName];
    
    NSDictionary *parameters = @{@"auth_msg":contextString,
                                 @"api_key":apiKey,
                                 @"api_secret":apiSecret};
    
    NSMutableArray *postArray = [NSMutableArray array];
    [parameters enumerateKeysAndObjectsUsingBlock:^(NSString *key, NSString *obj, BOOL *stop) {
        [postArray addObject:[NSString stringWithFormat:@"%@=%@", key, [self percentEscapeString:obj]]];
    }];
    NSString *postString = [postArray componentsJoinedByString:@"&"];
    NSData *postData = [postString dataUsingEncoding:NSUTF8StringEncoding];
    
    NSURL *tempURL = [NSURL URLWithString:MG_LICENSE_API];
    NSMutableURLRequest *netRequest = [NSMutableURLRequest requestWithURL:tempURL
                                                              cachePolicy:NSURLRequestUseProtocolCachePolicy
                                                          timeoutInterval:10];
    [netRequest setHTTPMethod:@"POST"];
    [netRequest setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    [netRequest setHTTPBody:postData];
    
    NSURLSession *urlSession = [NSURLSession sharedSession];
    
    NSURLSessionDataTask *dataTask = [urlSession dataTaskWithRequest:netRequest
                                                   completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
                                                       BOOL success = NO;
                                                       NSError *returnError = nil;
                                                       
                                                       if (!error){
                                                           NSDictionary *result = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];

                                                           if (result == NULL) {
                                                               NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

                                                               if (string) {
                                                                   success = [MGLicenseManager setLicense:string];
                                                               }else{
                                                                   returnError = [NSError errorWithDomain:NSCocoaErrorDomain
                                                                                                     code:101
                                                                                                 userInfo:@{@"messsage":@"服务器返回数据解析错误！"}];
                                                               }
                                                           }else{
                                                               returnError = [NSError errorWithDomain:NSCocoaErrorDomain code:100 userInfo:result];
                                                           }
                                                       }else{
                                                           returnError = error;
                                                       }
                                                       
                                                       if (finish) {
                                                           finish(success, returnError);
                                                       }
                                                   }];
    [dataTask resume];
    return dataTask;
}

+ (NSString *)percentEscapeString:(NSString *)string {
    NSCharacterSet *allowedCharacters = [NSCharacterSet characterSetWithCharactersInString:@"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-._~/?"];
    return [string stringByAddingPercentEncodingWithAllowedCharacters:allowedCharacters];
}


@end
