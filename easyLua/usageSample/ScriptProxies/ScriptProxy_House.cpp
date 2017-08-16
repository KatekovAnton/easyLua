//
//  ScriptProxy_House.cpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#include "ScriptProxy_House.hpp"
#include "LUAContext.hpp"



using namespace luabridge;
#define LUA context->LuaState()



void ScriptProxy_House::BindToContext(LUAContext *context)
{
    getGlobalNamespace(LUA)
    .beginClass<ScriptProxy_House>("House")
    .addCFunction("__tostring", &ScriptProxy_House::ToString)
    
    .addFunction("getSize", &ScriptProxy_House::ScriptProxy_GetSize)
    .addFunction("getRoomersCount", &ScriptProxy_House::ScriptProxy_GetRoomersCount)
    .addFunction("getRoomer", &ScriptProxy_House::ScriptProxy_GetRoomer)
    
    .endClass();
}

int ScriptProxy_House::ToString(lua_State* L)
{
    ScriptProxy_House* house = Userdata::get<ScriptProxy_House>(L, 1, true);
    std::string debugString = "House";
    lua_pushfstring(L, "%s (%p)", debugString.c_str(), house);
    return 1;
}

GSize2D ScriptProxy_House::ScriptProxy_GetSize()
{return GSize2D();}

int ScriptProxy_House::ScriptProxy_GetRoomersCount()
{return 0;}

ScriptProxy_Person *ScriptProxy_House::ScriptProxy_GetRoomer(int index)
{return NULL;}
