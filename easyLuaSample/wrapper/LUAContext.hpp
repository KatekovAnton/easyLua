//
//  LUAContext.hpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
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
class ByteBuffer;



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
    
    void Save(ByteBuffer *buffer);
    void Load(ByteBuffer *buffer);
    
#pragma mark - Object bindings
    
    void BindStructures();
    
};

#endif /* LUAContext_hpp */
