/* 
 * File:   main.cpp
 * Author: cross
 *
 * Created on December 2, 2009, 12:16 AM
 */

#include <stdlib.h>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include "LuaDebugger.h"
#include "LuaDebuggerConsole.h"

int my_function(lua_State* L) {
    int argc = lua_gettop(L);
    const char* c= lua_tostring(L, 1);
    printf("c: %s\n", c);
    lua_pushstring(L, "hello world");
    return 1;
}

void debug_function(lua_State* L, lua_Debug* d) {
    if (d->currentline == 3) {
        printf("aqui estoy");
    }
}
/*
 * 
 */
int main(int argc, char** argv) {

    lua_State* L;

    L = lua_open();
    luaL_openlibs(L);
    lua_register(L, "my_function", my_function);
    //   LUA_MASKRET, LUA_MASKLINE, LUA_MASKCALL and LUA_MASKCOUNT
    LuaDebugger d(L);
    LuaDebuggerConsole console;
    d.addBreakpoint(3);
    d.addBreakpoint(6);
    console.startConsole(&d);
    d.startDebug();
    luaL_dofile(L, "test.lua");
    lua_close(L);
    console.stopConsole();
    d.stopDebug();

    printf("print any key");
    getchar();
    return (EXIT_SUCCESS);
}

