//
//  Log.hpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
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
