//
//  ScriptProxy_House.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef ScriptProxy_House_hpp
#define ScriptProxy_House_hpp

#include <stdio.h>
#include "Geometry.h"



class LUAContext;
struct lua_State;
class ScriptProxy_Person;



class ScriptProxy_House {
    
public:
    
    // Binding method
    static void BindToContext(LUAContext *context);
    
    // Required for debugging using ZeroBrane Studio
    int ToString(lua_State* L);
    
    virtual GSize2D ScriptProxy_GetSize();
    virtual int ScriptProxy_GetRoomersCount();
    virtual ScriptProxy_Person *ScriptProxy_GetRoomer(int index);
    
};

#endif /* ScriptProxy_House_hpp */
