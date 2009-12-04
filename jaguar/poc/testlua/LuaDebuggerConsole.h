/* 
 * File:   LuaDebuggerConsole.h
 * Author: cross
 *
 * Created on December 3, 2009, 1:21 PM
 */

#ifndef _LUADEBUGGERCONSOLE_H
#define	_LUADEBUGGERCONSOLE_H

#include "LuaDebugger.h"

class LuaDebuggerConsole {
public:
    LuaDebuggerConsole();
    LuaDebuggerConsole(const LuaDebuggerConsole& orig);
    virtual ~LuaDebuggerConsole();

    void breakpoint(lua_Debug* debugInfo);
    
    void startConsole(LuaDebugger* _debugger);
    void stopConsole();

private:
    LuaDebugger* debugger;

    string* getCommand();
};

#endif	/* _LUADEBUGGERCONSOLE_H */

