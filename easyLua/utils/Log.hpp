//
//  Log.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/15/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef Log_hpp
#define Log_hpp

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif
    
    void ULogR(const char * pszFormat, ...);
    void ULog(const char * pszFormat, ...);
    
    
#ifdef __cplusplus
}
#endif

#endif /* Log_hpp */
