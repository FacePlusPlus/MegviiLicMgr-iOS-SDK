#ifndef _MG_LICENSEMANAGER_H_
#define _MG_LICENSEMANAGER_H_

#include "MG_Common.h"
#define MG_END_ARG NULL
#define _OUT
typedef enum {
    MG_LICMGR_DURATION_30DAYS = 30,
    MG_LICMGR_DURATION_365DAYS = 365
} MG_LICMGR_DURATION;

#if MGAPI_BUILD_ON_ANDROID
typedef struct {
    MG_RETCODE (*GetContext)(JNIEnv*, jobject, MG_LICMGR_DURATION duration, const char* uuid,  const char _OUT **context_data, MG_INT32 _OUT *context_length, ...);
    MG_RETCODE (*SetLicence)(JNIEnv*, jobject, const char *license_data, MG_INT32 license_length);
} MG_LICENSE_MANAGER_API_FUNCTIONS_TYPE;
#else
typedef struct {
    MG_RETCODE (*GetContext)(MG_LICMGR_DURATION duration, const char* uuid, const char _OUT **context_data, MG_INT32 _OUT *context_length, ...);
    MG_RETCODE (*SetLicence)(const char *license_data, MG_INT32 license_length);
} MG_LICENSE_MANAGER_API_FUNCTIONS_TYPE;
#endif

extern MG_EXPORT MG_LICENSE_MANAGER_API_FUNCTIONS_TYPE mg_licmgr;

#undef _OUT

#endif
