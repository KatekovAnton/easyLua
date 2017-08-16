//
//  LUAContext.hpp
//  MAX
//
//  Created by Katekov Anton on 2/16/16.
//  Copyright © 2016 AntonKatekov. All rights reserved.
//

#ifndef LUAContext_hpp
#define LUAContext_hpp

#include <stdio.h>



#if defined (ANDROID)
#define l_getlocaledecpoint()	('.')
#endif



#include "lua.hpp"
#include "LuaBridge.h"
#include "LUAContextDataSource.hpp"



class LUAHull;



class LUAContext {
    
    LUAHull *_luaHull;
    
public:
    
    LUAContextDataSource *_dataSource;
    
    LUAContext();
    ~LUAContext();
    
    lua_State* LuaState();
    
    void ExecuteTestFunctions();
    
    void LoadText(const std::string& text);
    void LogText(const std::string& text);
    
#pragma mark - Object bindings
    
    void BindStructures();
    
};

#endif /* LUAContext_hpp */
