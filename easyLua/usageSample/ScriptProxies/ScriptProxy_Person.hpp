//
//  ScriptProxy_Person.hpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#ifndef ScriptProxy_Person_hpp
#define ScriptProxy_Person_hpp

#include <stdio.h>
#include <string>
#include "Geometry.h"



class LUAContext;
struct lua_State;



class ScriptProxy_Person {
    
public:
    
    // Binding method
    static void BindToContext(LUAContext *context);
    
    // Required for debugging using ZeroBrane Studio
    int ToString(lua_State* L);
    
    virtual std::string ScriptProxy_GetName();
    virtual void ScriptProxy_SetName(std::string name);
    virtual GPoint2D ScriptProxy_GetPosition();
    virtual void ScriptProxy_SetPosition(GPoint2D position);
    
};

#endif /* ScriptProxy_Person_hpp */
