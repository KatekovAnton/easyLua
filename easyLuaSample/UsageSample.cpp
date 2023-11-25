//
//  UsageSample.cpp
//
//  Created by Anton Katekov on 01.01.2023.
//  Copyright (c) 2023 AntonKatekov. All rights reserved.
//

#include "UsageSample.hpp"
#include <string>
#include <vector>
#include "wrapper/LUAContext.hpp"
#include "SampleObjects/Person.hpp"
#include "SampleObjects/House.hpp"
#include "FileManger.h"
#include "Log.hpp"
#include <memory>



using namespace std;
using namespace luabridge;



UsageSample::UsageSample()
{
    _rootFolder = "Scripts/";

    vector<shared_ptr<Person>> persons;
    persons.push_back(shared_ptr<Person>(new Person("Fredd", GPoint2D(0.3, 0.7))));
    persons.push_back(shared_ptr<Person>(new Person("Sarah", GPoint2D(0.9, 1.5))));
    _house = new House(persons, GSize2D(2.0, 2.0));
}

UsageSample::~UsageSample()
{
    delete _house;
}

void UsageSample::Test(ByteBuffer *destination)
{
    ULog("Usage sample: Test() begin ------");
    
    // create context
    LUAContext context;
    // data source for loading external modules
    context._dataSource = this;
    // binding common structures
    context.BindStructures();
    // binding classes
    ScriptProxy_House::BindToContext(&context);
    ScriptProxy_Person::BindToContext(&context);
    
    // load script text
    {
        string scriptText = "";
        shared_ptr<IFile> file = FileManager::SharedManager()->LoadFile("Scripts/testScript.lua");
        scriptText = file->GetContentAsString();
        
        context.LoadText(scriptText);
    }
    
    // call simple function
    try
    {
        LuaRef testSimpleFunction = getGlobal(context.LuaState(), "testSimpleFunction");
        if (testSimpleFunction.isFunction()) {
            testSimpleFunction();
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in testSimpleFunction: %s", e.what());
    }
    
    // call function with native data
    try
    {
        LuaRef testNativeObject = getGlobal(context.LuaState(), "testNativeObject");
        if (testNativeObject.isFunction())
        {
            // to pass house to the script we
            // HAVE to convert it to the script-understandable class
            ScriptProxy_House *house = reinterpret_cast<ScriptProxy_House *>(_house);
            
            testNativeObject(house);
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in testNativeObject: %s", e.what());
    }
    
    // run quest
    try
    {
        LuaRef initialiseQuest = getGlobal(context.LuaState(), "initialiseQuest");
        if (initialiseQuest.isFunction())
        {
            ScriptProxy_House *house = reinterpret_cast<ScriptProxy_House *>(_house);
            initialiseQuest(house);
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in initialiseQuest: %s", e.what());
    }
    
    ULog("Usage sample: running even without changes");
    // run check if roomer is there
    try
    {
        LuaRef onEvent = getGlobal(context.LuaState(), "onEvent");
        if (onEvent.isFunction())
        {
            ScriptProxy_House *house = reinterpret_cast<ScriptProxy_House *>(_house);
            onEvent(house);
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in onEvent: %s", e.what());
    }
    
    ULog("Usage sample: adding 3rd user and running event");
    _house->AddRoomer(shared_ptr<Person>(new Person("Anton", GPoint2D(0.6, 1.0))));
    
    // again run check if roomer is there
    try
    {
        LuaRef onEvent = getGlobal(context.LuaState(), "onEvent");
        if (onEvent.isFunction())
        {
            ScriptProxy_House *house = reinterpret_cast<ScriptProxy_House *>(_house);
            onEvent(house);
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in onEvent: %s", e.what());
    }
    
    ULog("Usage sample: adding 4th user and running event");
    _house->AddRoomer(shared_ptr<Person>(new Person("Mike", GPoint2D(0.1, 0.1))));
    
    // again run check if roomer is there
    try
    {
        LuaRef onEvent = getGlobal(context.LuaState(), "onEvent");
        if (onEvent.isFunction())
        {
            ScriptProxy_House *house = reinterpret_cast<ScriptProxy_House *>(_house);
            onEvent(house);
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in onEvent: %s", e.what());
    }
    
    // saving data to table
    try
    {
        LuaRef saveGlobalData = getGlobal(context.LuaState(), "saveGlobalData");
        if (saveGlobalData.isFunction()) {
            saveGlobalData();
        }
    }
    catch (LuaException const& e)
    {
        ULog("Error in saveGlobalData: %s", e.what());
    }
    
    lua_getglobal(context.LuaState(), "perms");
    lua_getglobal(context.LuaState(), "globalData");
    
//    lua_getglobal(context.LuaState(), -2);
    
    context.Save(destination);
    
    ULog("Usage sample: Test() done ------\n");
}

void UsageSample::TestSaved(ByteBuffer *source)
{
    ULog("Usage sample: TestSaved() begin ------");
    
    // create context
    LUAContext context;
    // data source for loading external modules
    context._dataSource = this;
    // binding common structures
    context.BindStructures();
    // binding classes
    ScriptProxy_House::BindToContext(&context);
    ScriptProxy_Person::BindToContext(&context);
    
    // load script text
    {
        string scriptText = "";
        shared_ptr<IFile> file = FileManager::SharedManager()->LoadFile("Scripts/testScript.lua");
        scriptText = file->GetContentAsString();
        
        context.LoadText(scriptText);
    }
    
    
    lua_getglobal(context.LuaState(), "perms");
    context.Load(source);
    LuaRef persRef = luabridge::LuaRef::fromStack(context.LuaState(), -1);
//    if (persRef.isTable()) {
//        LuaRef v3 = persRef["value3"];
//
//        if (v3.isString()) {
//            std::string s = v3.cast<std::string>();
//            ULog("%s", s.c_str());
//        }
//    }
    LuaRef loadGlobalData = getGlobal(context.LuaState(), "loadGlobalData");
    loadGlobalData(persRef);
    ULog("Usage sample: TestSaved() done ------");
}
