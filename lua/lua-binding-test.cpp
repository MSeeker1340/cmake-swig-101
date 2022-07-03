extern "C"
{
// Lua headers (core and swig-generated) need to be included as C
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

extern int luaopen_mylib(lua_State*);
}

namespace
{
    const char* SCRIPT = R"(
print("Testing mylib extension module ...")
print("mylib.addOne(1.0) = "..tostring(mylib.addOne(1.0)))
    )";
}

int main()
{
    auto* L = luaL_newstate();
    luaopen_base(L); // load basic libs
    luaopen_mylib(L); // load wrapped lib

    luaL_dostring(L, SCRIPT);

    lua_close(L);

    return 0;
}