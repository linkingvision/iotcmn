//
// Copyright(c) 2019 linkingvision.com
// Distributed under Commercial license info@linkingvision.com
//
#ifndef __IOT_TYPE_H__
#define __IOT_TYPE_H__
#ifdef __cplusplus

#include <string.h>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm> 
#include <cctype> 

#if defined(_WIN32)
#if defined(IOT_EXPORTS)
	#define IOT_LIBRARY_API __declspec(dllexport)
#else
	#define IOT_LIBRARY_API __declspec(dllimport)
#endif
#else
	#define IOT_LIBRARY_API
#endif

#ifndef  V_TYPE
#define V_TYPE
typedef  unsigned char u8;
typedef  char s8;
typedef  unsigned short u16;
typedef  short s16;
typedef  unsigned int  u32;
typedef  int s32;
#if defined(__GNUC__)
#if defined(__LP64__)
typedef  long  s64;
typedef  unsigned  long u64;
#else
typedef  long long s64;
typedef  unsigned  long long u64;
#endif
#else
typedef  long long s64;
typedef  unsigned  long long u64;
#endif

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;
typedef double DATE;

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed long long    INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long  UINT64, *PUINT64;

#ifndef TRUE 
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#endif /* V_TYPE */

#ifndef _WIN32
#ifndef ntohll
#if __BYTE_ORDER == __BIG_ENDIAN
/* The host byte order is the same as network byte order,
   so these functions are all just identity.  */
    #define ntohll(x)       (x)
    #define htonll(x)       (x)
#else 
    #if __BYTE_ORDER == __LITTLE_ENDIAN
    #define htonll(x)   ((((u64)htonl(x)) << 32) + htonl(x >> 32))
    #define ntohll(x)   ((((u64)ntohl(x)) << 32) + ntohl(x >> 32))
    #endif
#endif
#endif
#endif



enum IotLogLevel
{
	IotLogERROR, 
	IotLogWARNING, 
	IotLogINFO, 
	IotLogDEBUG
};

class IIotLogInterface
{
public:
	virtual void Log(IotLogLevel level, char* str) = 0;
};

inline void IotSleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


// Return value: bool (true on success, false on failure)
// Input parameters: md5 string, replacement string
// Output parameter: out_uuid (stores the final formatted UUID)
inline bool iot_md5_to_uuid(const std::string& md5, std::string& out_uuid, 
		std::string replacement = "AN") {
    // 1. Basic validation: Return false if MD5 length is not exactly 32 characters
    if (md5.length() != 32) {
        return false;
    }
    
    // 2. Format the standard UUID structure by inserting hyphens
    std::string uuid = md5.substr(0, 8) + "-" +
                       md5.substr(8, 4) + "-" +
                       md5.substr(12, 4) + "-" +
                       md5.substr(16, 4) + "-" +
                       md5.substr(20, 12);
                       
    // 3. Convert the entire UUID string to uppercase
    std::transform(uuid.begin(), uuid.end(), uuid.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    
    // 4. Convert the replacement string to uppercase to maintain consistency
    std::transform(replacement.begin(), replacement.end(), replacement.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    
    // 5. Length validation: Return false if replacement length exceeds the total UUID length (36 characters)
    if (replacement.length() > uuid.length()) {
        return false;
    }
    
    // 6. Perform the prefix replacement and assign the result to the output parameter
    uuid.replace(0, replacement.length(), replacement);
    out_uuid = uuid; 
    
    return true;
}



#endif /* __cplusplus */

#endif /* __IOT_TYPE_H__ */
