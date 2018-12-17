# easyLua

## Overview
This is a short example of how you can integrate lua interpreter into your c++ project and use it as embedded scripting language.

Platforms: iOS, MacOS

## Architecture
Hosting c++ application is a master, it is providing sandbox for embedded scripting, embedded scripting language works inside of sandbox, scripts can interact with hosting app through API.

Your primary goal is to design your scripting sandbox and API.

## Supported features
- Wrapping lua library
- Handling lua's `require('***')` instructions
- Binding structures for interacting with lua
- Sending structures into lua by value (transfering ownershipt to lua side)
- Binding classes via abstract ScriptProxy_ interfaces
- Sending classes into lua by pointer (keep ownershipt at hosting app side)

## Project structure
### Folders:
- **sys** - platform abstraction interface
- **utils** - project-agnostic utilities
- **vendors** - 3rd party libraries (lua, luaBridge, eris)
- **wrapper** - c++ wrappers for c libraries
- **usageSample** - combine everything together

### Key components:
- **LUAContext** - wrapper for lua state.
- **LUAContextDataSource** - abstract interface for handling lua's `require('***')` instructions. In real project you might need to load external modules from web, or from memory or from somewhere else - just implement the same interface and pass it into LUAContext.
- **LUAScriptDataSource** - example implementation of previous interface. This implementation will load external modules from application bundle.
- **ScriptProxy_...** - C++ interfaces that will be represented inside of scripting API
- **SampleObjects** - The actual objects that supposed to be represented in scripting API and used by scripts. Each of this objects implements corresponded ScriptProxy_ interface, that defines its API. This is a good place to validate script calls.

## More features to add
- Debugger with LuaSocket + Zerobrane studio
- Persist lua state using eris
- Android build
- Win build (win32 api)


