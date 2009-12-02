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
    lua_sethook(L, &debug_function, LUA_MASKLINE, 5);
    //   LUA_MASKRET, LUA_MASKLINE, LUA_MASKCALL and LUA_MASKCOUNT
    luaL_dofile(L, "test.lua");
    lua_close(L);

    printf("print any key");
    getchar();
    return (EXIT_SUCCESS);
}

