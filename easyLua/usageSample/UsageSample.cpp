//
//  UsageSample.cpp
//  easyLua
//
//  Created by Katekov Anton on 8/15/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#include "UsageSample.hpp"
#include <string>
#include <vector>
#include "LUAContext.hpp"
#include "Person.hpp"
#include "House.hpp"
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

void UsageSample::Test()
{
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
}
