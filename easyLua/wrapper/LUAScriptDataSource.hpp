//
//  LUAScriptDataSource.hpp
//  MAX
//
//  Created by Katekov Anton on 3/4/17.
//  Copyright © 2017 AntonKatekov. All rights reserved.
//

#ifndef LUAScriptDataSource_hpp
#define LUAScriptDataSource_hpp

#include <stdio.h>
#include "LUAContextDataSource.hpp"



class LUAScriptDataSource : public LUAContextDataSource {
    
protected:
    
    std::string _rootFolder;
    
#pragma mark - LUAContextDataSource
    
public:
    
    bool CanLoadModule(LUAContext *context, const std::string &moduleName) override;
    LUAModuleData LoadModule(LUAContext *context, const std::string &moduleName) override;
    
};

#endif /* ScriptDataSource_hpp */
