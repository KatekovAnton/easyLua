//
//  Log.cpp
//  MAX
//
//  Created by Katekov Anton on 11/15/12.
//  Copyright © 2012 katekovanton. All rights reserved.
//

#include "Log.hpp"
#include "stdarg.h"

#ifdef ANDROID

#include <android/log.h>

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "native-activity", __VA_ARGS__))
#endif


void ULog(const char * pszFormat, ...)
{
#if defined RELEASE
    return;
#endif
    
    
    char szBuf[16*1024];
    
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, 16*1024, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
    
    
#ifdef ANDROID
    LOGD("%s", szBuf);
#endif
}
