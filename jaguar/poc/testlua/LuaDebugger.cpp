/* 
 * File:   LuaDebugger.cpp
 * Author: cross
 * 
 * Created on December 3, 2009, 1:04 PM
 */

#include "LuaDebugger.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

LuaDebugger* debugger;

void hook(lua_State* L, lua_Debug* debugInfo) {
    debugger->doCallback(L, debugInfo);
}

LuaDebugger::LuaDebugger(lua_State* _luaState) {
    luaState = _luaState;
    breakpoints = NULL;
    cbreakpoints = 0;
    debugger = this;
}

LuaDebugger::~LuaDebugger() {
    if (breakpoints) {
        free(breakpoints);
    }
}

void LuaDebugger::addBreakpoint(int line) {
    if (cbreakpoints > 0) {
        int* current = breakpoints;
        breakpoints = (int*)malloc(sizeof(int)*(cbreakpoints+1));
        *breakpoints = *current;
        free(current);
    } else {
        breakpoints = (int*)malloc(sizeof(int)*(cbreakpoints+1));
    }
    breakpoints[cbreakpoints] = line;
    cbreakpoints++;
}

void LuaDebugger::startDebug() {
    int res = lua_sethook(luaState, &hook, LUA_MASKLINE, 0);
    debugging = true;
}

void LuaDebugger::stopDebug() {
    int res = lua_sethook(luaState, &hook, 0, 0);
    debugging = false;
}

void LuaDebugger::setCallback(brk_callback _callbackFunction) {
    callbackFunction = _callbackFunction;
}

void LuaDebugger::doCallback(lua_State* L, lua_Debug* d) {
    if (d->event == LUA_HOOKLINE) {
        int currentline = d->currentline;
        for (int x = 0; x < cbreakpoints; x++) {
            if (breakpoints[x] == currentline) {
                callbackFunction(L, d);
            }
        }
    }
}

void get_upvalues(lua_State* L) {
    const char* name = NULL;
    int i = 1;
    int top = lua_gettop(L);
    if (lua_isfunction(L, top)) {
        while ((name = lua_getupvalue(L, top, i++)) != NULL) {
            cout << "up: " << name << endl;
        }
    }
}

string* LuaDebugger::getStack2(lua_Debug* debugInfo) {
    lua_State* L = luaState;
    lua_getstack(L, 0, debugInfo);
    lua_getfield(L, LUA_GLOBALSINDEX, "n");
    const char* c = lua_tostring(L, -1);
    if (c) {
        cout << "getStack2: " << c << endl;
    }
    lua_pop(L, 1);
}

string* LuaDebugger::getStack(lua_Debug* debugInfo) {
    lua_Debug debug;
    int level = 0;

    while (lua_getstack(luaState, level++, &debug) == 1) {
        const char* name ;
        int i = 1;
        while ((name = lua_getlocal(luaState, &debug, i++)) != NULL) {
            cout << "local: " << name << endl;
            lua_pop(luaState, 1);
        }

        if (lua_getinfo(luaState, "SInfu", &debug) == 1) {
            get_upvalues(luaState);
        }
    }
}