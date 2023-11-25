//
//  ScriptProxy_Person.cpp
//  easyLua
//
//  Created by Katekov Anton on 8/16/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#include "ScriptProxy_Person.hpp"
#include "wrapper/LUAContext.hpp"



using namespace luabridge;
#define LUA context->LuaState()



void ScriptProxy_Person::BindToContext(LUAContext *context)
{
    getGlobalNamespace(LUA)
    .beginClass<ScriptProxy_Person>("Person")
    .addCFunction("__tostring", &ScriptProxy_Person::ToString)
    
    .addFunction("getName", &ScriptProxy_Person::ScriptProxy_GetName)
    .addFunction("setName", &ScriptProxy_Person::ScriptProxy_SetName)
    .addFunction("getPosition", &ScriptProxy_Person::ScriptProxy_GetPosition)
    .addFunction("setPosition", &ScriptProxy_Person::ScriptProxy_SetPosition)
    
    .endClass();
}

int ScriptProxy_Person::ToString(lua_State* L)
{
    ScriptProxy_Person* person = Userdata::get<ScriptProxy_Person>(L, 1, true);
    std::string debugString = "Person " + ScriptProxy_GetName();
    lua_pushfstring(L, "%s (%p)", debugString.c_str(), person);
    return 1;
}

std::string ScriptProxy_Person::ScriptProxy_GetName()
{return "";}

void ScriptProxy_Person::ScriptProxy_SetName(std::string name)
{}

GPoint2D ScriptProxy_Person::ScriptProxy_GetPosition()
{return GPoint2D();}

void ScriptProxy_Person::ScriptProxy_SetPosition(GPoint2D position)
{}
