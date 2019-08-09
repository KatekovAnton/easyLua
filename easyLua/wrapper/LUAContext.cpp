//
//  LUAContext.cpp
//  MAX
//
//  Created by Katekov Anton on 2/16/16.
//  Copyright © 2016 AntonKatekov. All rights reserved.
//

#include "LUAContext.hpp"
#include "FileManger.h"
#include "Log.hpp"
#include <vector>
#if !defined (WIN32)
extern "C" {
#endif
#include "eris.h"
#if !defined (WIN32)
}
#endif
#include "ByteBuffer.h"



using namespace std;
using namespace luabridge;


class LUAPersister {
public:
    
    size_t _position;
    
    LUAContext *_context;
    ByteBuffer *_data;
    
    LUAPersister(LUAContext *context,
              ByteBuffer *data)
    :_context(context)
    ,_data(data)
    ,_position(0)
    {}
};


const char * lua_Reader_impl(lua_State *L, void *ud, size_t *sz) {
    LUAPersister *persister = (LUAPersister *)ud;
    const char *result = reinterpret_cast<const char *>(persister->_data->getPointer());
    *sz = persister->_data->getDataSize();
    return result;
}

int lua_Writer_impl(lua_State *L, const void *p, size_t sz, void *ud) {
    LUAPersister *persister = (LUAPersister *)ud;
    persister->_data->appendData(reinterpret_cast<const unsigned char *>(p), sz, 1);
    return 0;
}



static std::vector<LUAContext*> allContexts;

/*
 Well, that was pretty rough but I figured it out finally. Turns out that when you call "require" LUA accesses the global "package.loaders" table, which contains a list of functions which searches for and loads your particular lua file.
 
 So, the trick is to add your own function at the end of package.loaders. If the file count not be loaded, push a new string onto the stack explaining why (or nil). If you could load it fine, just return the new buffer/file you loaded. That's all.
 
 Example:
 */

int MyLoader(lua_State* pState)
{
    LUAContext *owner = NULL;
    for (int i = 0; i < allContexts.size(); i++) {
        if (allContexts[i]->LuaState() == pState) {
            owner = allContexts[i];
            break;
        }
    }
    if (!owner) {
        ///
    }
    
    LUAModuleData moduleData;
    moduleData.moduleName = lua_tostring(pState, 1);
    bool loaded = false;
    
    if (owner->_dataSource)
    {
        loaded = owner->_dataSource->CanLoadModule(owner, moduleData.moduleName);
        if (loaded)
            moduleData = owner->_dataSource->LoadModule(owner,moduleData.moduleName);
    }
    else
    {
        moduleData.moduleName += ".lua";
        
        shared_ptr<IFile> file = FileManager::SharedManager()->LoadFile(moduleData.moduleName);
        if(file)
        {
            loaded = true;

            moduleData.moduleText = file->GetContentAsString();
            moduleData.moduleFullName = FileManager::SharedManager()->GetFilePath(moduleData.moduleName);
        }
    }
    
    if (loaded)
    {
        luaL_loadbuffer(pState, moduleData.moduleText.c_str(), moduleData.moduleText.length(), moduleData.moduleFullName.c_str());
    }
    else
    {
        std::string err = "\n\tError - MyLoader could not find ";
        err += moduleData.moduleName;
        err += ".";
        lua_pushstring(pState, err.c_str());
    }
    
    return 1;
}



class LUAHull
{
    
public:
    
    lua_State *_l;
    
    LUAHull();
    ~LUAHull();
    
    void ExecuteCode(const string &code);
    void RetrieveError();
    void LogText(const string &text, const string &context);
    
    void EnableCustomLoader();
};

LUAHull::LUAHull()
:
_l(luaL_newstate())
{
    luaL_openlibs(_l);
    EnableCustomLoader();
}

LUAHull::~LUAHull()
{
    lua_close(_l);
}

void LUAHull::ExecuteCode(const string &code)
{
    int status = luaL_dostring(_l, code.c_str());
    if(status!=0) {
        // error
        RetrieveError();
    }
}

void LUAHull::RetrieveError()
{
    LogText(lua_tostring(_l, -1), "Error");
    lua_pop(_l, 1);  /* pop error message from the stack */
}

void LUAHull::LogText(const string &text, const string &context)
{
    if (context.length() > 0) {
        ULog("lua: %s: %s", context.c_str(), text.c_str());
    }
    else {
        ULog("lua: %s", text.c_str());
    }
}

void LUAHull::EnableCustomLoader()
{
    LuaRef package = getGlobal(_l, "package");
    LuaRef loaders = package["loaders"];
    loaders[loaders.length()] = &MyLoader;
    return;
}


#define LUA _luaHull->_l

LUAContext::LUAContext()
:
_luaHull(new LUAHull()),
_dataSource(NULL)
{
    allContexts.push_back(this);
    
    getGlobalNamespace(LUA)
    .beginClass<LUAContext>("LUAContext")
        .addFunction ("logtext", &LUAContext::LogText)
    .endClass ();
    
    // push variable and give its name
    push (LUA, this); // push context to lua stack
    lua_setglobal (LUA, "context"); // call "context" top variable and pop it
    
#if LUA_OPEN_SOCKETS_LIB
    push(LUA, true);
    lua_setglobal (LUA, "RemoteDebugEnabled");
#endif
}

lua_State* LUAContext::LuaState()
{
    return LUA;
}

void LUAContext::ExecuteTestFunctions()
{
    // simple sample
    string text = "\
    function subtract(a, b)\
    return a - b, 'hello'\
    end\
    \
    function multiply(a, b)\
    return a * b, 'hello'\
    end";
    _luaHull->ExecuteCode(text.c_str());
    
    
    //how to retrieve 'hello'???!!!!
    {
        LuaRef function = getGlobal (LUA, "subtract");
        LuaRef result = function(20, 800);
        int resutltInt = result.cast<int>();
        resutltInt = resutltInt;
    }
    
    // I didnt extract hello and it works fine
    // means 'hello' is not on the stack
    {
        LuaRef function = getGlobal (LUA, "multiply");
        LuaRef result = function(24, 32);
        int resutltInt = result.cast<int>();
        resutltInt = resutltInt;
    }
    
    //https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/
    //https://eliasdaler.wordpress.com/2014/07/18/using-lua-with-cpp-luabridge/
    //http://a8u-tutorial-sources.googlecode.com/git-history/311fd6c18b5548db7d52f1e59eaf45c1a37b5533/Game/External/LuaBridge-2.0/Manual.html
    
}

LUAContext::~LUAContext()
{
    allContexts.erase(std::find(allContexts.begin(), allContexts.end(), this));
    
    delete _luaHull;
    _luaHull = NULL;
}

void LUAContext::LoadText(const std::string& text)
{
    _luaHull->ExecuteCode(text);
}

void LUAContext::LogText(const std::string& text)
{
    _luaHull->LogText(text, "");
}

void LUAContext::Save(ByteBuffer *buffer)
{
    LUAPersister p(this, buffer);
    eris_dump(LUA, &lua_Writer_impl, &p);
}

void LUAContext::Load(ByteBuffer *buffer)
{
    LUAPersister p(this, buffer);
    eris_undump(LUA, &lua_Reader_impl, &p);
}

#pragma mark - Object bindings

void LUAContext::BindStructures()
{
    getGlobalNamespace(LUA)
    .beginClass<GPoint2D>("Point")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (float, float)>()
        .addProperty("x", &GPoint2D::getX, &GPoint2D::setX)
        .addProperty("y", &GPoint2D::getY, &GPoint2D::setY)
    .endClass();
    
    getGlobalNamespace(LUA)
    .beginClass<GSize2D>("Size")
    .addConstructor<void(*) ()>()
    .addConstructor<void(*) (float, float)>()
    .addProperty("w", &GSize2D::getW, &GSize2D::setW)
    .addProperty("h", &GSize2D::getH, &GSize2D::setH)
    .endClass();
    
    getGlobalNamespace(LUA)
    .beginClass<GRect2D>("Rect")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (float, float, float, float)>()
        .addProperty("x", &GRect2D::getX, &GRect2D::setX)
        .addProperty("y", &GRect2D::getY, &GRect2D::setY)
        .addProperty("w", &GRect2D::getW, &GRect2D::setW)
        .addProperty("h", &GRect2D::getH, &GRect2D::setH)
    .endClass();
    
}
