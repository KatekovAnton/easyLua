//
//  LUAContextDataSource.hpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#ifndef LUAContextDataSource_hpp
#define LUAContextDataSource_hpp

#include <string>



class LUAContext;



typedef struct __LUAModuleData {
    
    std::string moduleName;
    std::string moduleFullName;
    std::string moduleText;
    
} LUAModuleData;



class LUAContextDataSource {
    
public:
    
    virtual bool CanLoadModule(LUAContext *context, const std::string &moduleName) = 0;
    virtual LUAModuleData LoadModule(LUAContext *context, const std::string &moduleName) = 0;
    
};

#endif /* LUAContextDataSource_hpp */
