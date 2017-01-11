/**
 * @file Common header of MGFace API.
 *
 * @copyright Copyright (c) 2013 Megvii Inc. All rights reserved.
 */

#ifndef _MG_COMMON_H_
#define _MG_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    MG_RETCODE_OK = 0,
    MG_RETCODE_INVALID_ARGUMENT,
    MG_RETCODE_INVALID_HANDLE,
    MG_RETCODE_INDEX_OUT_OF_RANGE,

    MG_RETCODE_EXPIRE = 101,
    MG_RETCODE_INVALID_BUNDLEID,
    MG_RETCODE_INVALID_LICENSE,
    MG_RETCODE_INVALID_MODEL,

    MG_RETCODE_FAILED = -1
} MG_RETCODE;

#define MGFACEAPI_LIBRARY

#if defined(_WIN32)

#if defined(MGFACEAPI_LIBRARY)
#define MG_EXPORT __declspec(dllexport)
#else
#define MG_EXPORT __declspec(dllimport)
#endif

#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__GNUC__)

#if defined(MGFACEAPI_LIBRARY)
#define MG_EXPORT __attribute__ ((visibility ("default")))
#else
#define MG_EXPORT
#endif

#endif

#define MGOUT

/**
 * Define basic types
 */
#ifndef MG_BASIC_TYPES
#if defined(unix) || defined(__unix__) || defined(__unix) || defined (__APPLE__) || defined(__MINGW_GCC) || defined(__MINGW32__)
#include <stdint.h>
typedef int8_t             MG_INT8;
typedef int16_t            MG_INT16;
typedef int32_t            MG_INT32;
typedef int64_t            MG_INT64;
typedef uint8_t            MG_UINT8;
typedef uint16_t           MG_UINT16;
typedef uint32_t           MG_UINT32;
typedef uint64_t           MG_UINT64;
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
typedef signed __int8      MG_INT8;
typedef signed __int16     MG_INT16;
typedef signed __int32     MG_INT32;
typedef signed __int64     MG_INT64;
typedef unsigned __int8    MG_UINT8;
typedef unsigned __int16   MG_UINT16;
typedef unsigned __int32   MG_UINT32;
typedef unsigned __int64   MG_UINT64;
#else
typedef signed char        MG_INT8;
typedef signed short       MG_INT16;
typedef int                MG_INT32;
typedef long long          MG_INT64;
typedef unsigned char      MG_UINT8;
typedef unsigned short     MG_UINT16;
typedef unsigned int       MG_UINT32;
typedef unsigned long long MG_UINT64;
#endif

typedef float MG_SINGLE;
typedef double MG_DOUBLE;
typedef unsigned char MG_BYTE;
typedef int MG_BOOL;
#ifndef NULL
#define NULL 0
#endif
#define MG_BASIC_TYPES
#endif


/**
 * check build platforms
 */
#if __APPLE__
        #include <UIKit/UIKit.h>
        #define MGAPI_BUILD_ON_IPHONE   1
#elif __ANDROID__
#define MGAPI_BUILD_ON_ANDROID	1
#include <jni.h>
#elif __linux
#define MGAPI_BUILD_ON_LINUX    1
#else
#error "unsupported platform"
#endif

/*
 * Define basic structures
 */
typedef struct {
    MG_SINGLE x;
    MG_SINGLE y;
} MG_POINT;

typedef struct {
    MG_INT32 left;
    MG_INT32 top;
    MG_INT32 right;
    MG_INT32 bottom;
} MG_RECTANGLE;

typedef enum{
    MG_IMAGEMODE_GRAY = 0,
    MG_IMAGEMODE_BGR,
    MG_IMAGEMODE_NV21,
    MG_IMAGEMODE_RGBA,
    MG_IMAGEMODE_RGB,

    // supported image type count
    MG_IMAGEMODE_COUNT
} MG_IMAGEMODE;




#define MG_LEFT_EYE_PUPIL 0
#define MG_LEFT_EYE_LEFT_CORNER 1
#define MG_LEFT_EYE_RIGHT_CORNER 2
#define MG_LEFT_EYE_TOP 3
#define MG_LEFT_EYE_BOTTOM 4
#define MG_LEFT_EYE_UPPER_LEFT_QUARTER 5
#define MG_LEFT_EYE_LOWER_LEFT_QUARTER 6
#define MG_LEFT_EYE_UPPER_RIGHT_QUARTER 7
#define MG_LEFT_EYE_LOWER_RIGHT_QUARTER 8
#define MG_RIGHT_EYE_PUPIL 9
#define MG_RIGHT_EYE_LEFT_CORNER 10
#define MG_RIGHT_EYE_RIGHT_CORNER 11
#define MG_RIGHT_EYE_TOP 12
#define MG_RIGHT_EYE_BOTTOM 13
#define MG_RIGHT_EYE_UPPER_LEFT_QUARTER 14
#define MG_RIGHT_EYE_LOWER_LEFT_QUARTER 15
#define MG_RIGHT_EYE_UPPER_RIGHT_QUARTER 16
#define MG_RIGHT_EYE_LOWER_RIGHT_QUARTER 17
#define MG_LEFT_EYEBROW_LEFT_CORNER 18
#define MG_LEFT_EYEBROW_RIGHT_CORNER 19
#define MG_LEFT_EYEBROW_UPPER_MIDDLE 20
#define MG_LEFT_EYEBROW_LOWER_MIDDLE 21
#define MG_LEFT_EYEBROW_UPPER_LEFT_QUARTER 22
#define MG_LEFT_EYEBROW_LOWER_LEFT_QUARTER 23
#define MG_LEFT_EYEBROW_UPPER_RIGHT_QUARTER 24
#define MG_LEFT_EYEBROW_LOWER_RIGHT_QUARTER 25
#define MG_RIGHT_EYEBROW_LEFT_CORNER 26
#define MG_RIGHT_EYEBROW_RIGHT_CORNER 27
#define MG_RIGHT_EYEBROW_UPPER_MIDDLE 28
#define MG_RIGHT_EYEBROW_LOWER_MIDDLE 29
#define MG_RIGHT_EYEBROW_UPPER_LEFT_QUARTER 30
#define MG_RIGHT_EYEBROW_LOWER_LEFT_QUARTER 31
#define MG_RIGHT_EYEBROW_UPPER_RIGHT_QUARTER 32
#define MG_RIGHT_EYEBROW_LOWER_RIGHT_QUARTER 33
#define MG_NOSE_TIP 34
#define MG_NOSE_CONTOUR_LOWER_MIDDLE 35
#define MG_NOSE_CONTOUR_LEFT1 36
#define MG_NOSE_CONTOUR_RIGHT1 37
#define MG_NOSE_CONTOUR_LEFT2 38
#define MG_NOSE_CONTOUR_RIGHT2 39
#define MG_NOSE_LEFT 40
#define MG_NOSE_RIGHT 41
#define MG_NOSE_CONTOUR_LEFT3 42
#define MG_NOSE_CONTOUR_RIGHT3 43
#define MG_MOUTH_LEFT_CORNER 44
#define MG_MOUTH_RIGHT_CORNER 45
#define MG_MOUTH_UPPER_LIP_TOP 46
#define MG_MOUTH_UPPER_LIP_BOTTOM 47
#define MG_MOUTH_UPPER_LIP_LEFT_CONTOUR1 48
#define MG_MOUTH_UPPER_LIP_RIGHT_CONTOUR1 49
#define MG_MOUTH_UPPER_LIP_LEFT_CONTOUR2 50
#define MG_MOUTH_UPPER_LIP_RIGHT_CONTOUR2 51
#define MG_MOUTH_UPPER_LIP_LEFT_CONTOUR3 52
#define MG_MOUTH_UPPER_LIP_RIGHT_CONTOUR3 53
#define MG_MOUTH_LOWER_LIP_TOP 54
#define MG_MOUTH_LOWER_LIP_BOTTOM 55
#define MG_MOUTH_LOWER_LIP_LEFT_CONTOUR1 56
#define MG_MOUTH_LOWER_LIP_RIGHT_CONTOUR1 57
#define MG_MOUTH_LOWER_LIP_LEFT_CONTOUR2 58
#define MG_MOUTH_LOWER_LIP_LEFT_CONTOUR3 59
#define MG_MOUTH_LOWER_LIP_RIGHT_CONTOUR3 60
#define MG_MOUTH_LOWER_LIP_RIGHT_CONTOUR2 61
#define MG_CONTOUR_LEFT1 62
#define MG_CONTOUR_RIGHT1 63
#define MG_CONTOUR_CHIN 64
#define MG_CONTOUR_LEFT2 65
#define MG_CONTOUR_LEFT3 66
#define MG_CONTOUR_LEFT4 67
#define MG_CONTOUR_LEFT5 68
#define MG_CONTOUR_LEFT6 69
#define MG_CONTOUR_LEFT7 70
#define MG_CONTOUR_LEFT8 71
#define MG_CONTOUR_LEFT9 72
#define MG_CONTOUR_RIGHT2 73
#define MG_CONTOUR_RIGHT3 74
#define MG_CONTOUR_RIGHT4 75
#define MG_CONTOUR_RIGHT5 76
#define MG_CONTOUR_RIGHT6 77
#define MG_CONTOUR_RIGHT7 78
#define MG_CONTOUR_RIGHT8 79
#define MG_CONTOUR_RIGHT9 80

#define MG_LANDMARK_NR 81

typedef struct {
    MG_POINT point[MG_LANDMARK_NR];
} MG_FACELANDMARKS;

typedef struct {
    MG_SINGLE pitch;
    MG_SINGLE yaw;
    MG_SINGLE roll;
} MG_3DPOSE;

typedef struct {
    MG_SINGLE female;
    MG_SINGLE male;
} MG_GENDER;

typedef enum{
    MG_EYESTATUS_NOGLASSES_EYEOPEN = 0,
    MG_EYESTATUS_NOGLASSES_EYECLOSE = 1,
    MG_EYESTATUS_NORMALGLASSES_EYEOPEN = 2,
    MG_EYESTATUS_NORMALGLASSES_EYECLOSE = 3,
    MG_EYESTATUS_DARKGLASSES = 4,
    MG_EYESTATUS_OTHER_OCCLUSION = 5,
    MG_EYESTATUS_COUNT
} MG_EYESTATUS;

typedef enum {
    MG_MOUTHSTATUS_OPEN = 0,
    MG_MOUTHSTATUS_CLOSE = 1,
    MG_MOUTHSTATUS_MASK_OR_RESPIRATOR = 2,
    MG_MOUTHSTATUS_OTHER_OCCLUSION = 3,
    MG_MOUTHSTATUS_COUNT
} MG_MOUTHSTATUS;

typedef struct {
    /** tracking ID */
    MG_INT32 track_id;
    /** face bounding rectangle */
    MG_RECTANGLE rect;
    MG_FACELANDMARKS points;
    MG_SINGLE confidence;
    MG_3DPOSE pose;
    MG_SINGLE left_eyestatus[MG_EYESTATUS_COUNT];
    MG_SINGLE right_eyestatus[MG_EYESTATUS_COUNT];
    MG_SINGLE age;
    MG_GENDER gender;
    MG_SINGLE blurness;
    MG_SINGLE minority;
    MG_SINGLE moutstatus[MG_MOUTHSTATUS_COUNT];
} MG_FACE;


#ifdef __cplusplus
}
#endif

#endif // _MG_COMMON_H_
