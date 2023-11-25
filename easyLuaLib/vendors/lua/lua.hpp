// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

#if !defined (WIN32)
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#if !defined (WIN32)
}
#endif
