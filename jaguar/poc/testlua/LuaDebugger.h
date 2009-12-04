/* 
 * File:   LuaDebugger.h
 * Author: cross
 *
 * Created on December 3, 2009, 1:04 PM
 */

#ifndef _LUADEBUGGER_H
#define	_LUADEBUGGER_H

extern "C" {
    #include <lua5.1/lua.h>
    #include <lua5.1/lualib.h>
    #include <lua5.1/lauxlib.h>
}

#include <string>

using namespace std;

typedef void (*brk_callback) (lua_State *L, lua_Debug *ar);

class LuaDebugger {
public:
    LuaDebugger(lua_State* _luaState);
    virtual ~LuaDebugger();

    void addBreakpoint(int line);
    void startDebug();
    void stopDebug();

    void setCallback(brk_callback _callbackFunction);
    void doCallback(lua_State* L, lua_Debug* d);
    string* getStack(lua_Debug* debugInfo);
    string* getStack2(lua_Debug* debugInfo);
    
private:
    int* breakpoints;
    int cbreakpoints;
    lua_State* luaState;
    bool debugging;

    brk_callback callbackFunction;

};

#endif	/* _LUADEBUGGER_H */

