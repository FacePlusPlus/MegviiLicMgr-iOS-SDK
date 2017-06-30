//
//  MGLicenseCommon.h
//  MGMobileSDKAuth
//
//  Created by 张英堂 on 2017/1/10.
//  Copyright © 2017年 megvii. All rights reserved.
//

#ifndef MGLicenseCommon_h
#define MGLicenseCommon_h

//#define MG_LICENSE_API_DURATION     @"30"

typedef NS_ENUM(NSInteger, MGAPIDuration) {
    MGAPIDurationDay = 1,
    MGAPIDurationMonth = 30,
    MGAPIDurationYear = 365,
};

typedef NS_ENUM(NSInteger, MGSDKType) {
    MGSDKTypeLandmark = 1,
    MGSDKTypeIDCard = 2,
};

static NSString *MGLicenseURL_CN = @"https://api-cn.faceplusplus.com/sdk/v2/auth";
static NSString *MGLicenseURL_US = @"https://api-us.faceplusplus.com/sdk/v2/auth";
//#define MG_LICENSE_API_CN           @"https://api-cn.faceplusplus.com/sdk/v2/auth"
//#define MG_LICENSE_API_US           @"https://api-us.faceplusplus.com/sdk/v2/auth"


//#define MG_SDK_TYPE_LANDMARK        @"Landmark"
//#define MG_SDK_TYPE_IDCARD          @"IDCard"





#endif /* MGLicenseCommon_h */
