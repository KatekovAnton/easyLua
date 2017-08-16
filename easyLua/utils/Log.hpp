//
//  Log.hpp
//  MAX
//
//  Created by Katekov Anton on 11/15/12.
//  Copyright © 2012 katekovanton. All rights reserved.
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
