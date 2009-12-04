/* 
 * File:   LuaDebuggerConsole.cpp
 * Author: cross
 * 
 * Created on December 3, 2009, 1:21 PM
 */

#include "LuaDebuggerConsole.h"

#include <iostream>
#include <string.h>

using namespace std;

LuaDebuggerConsole* console;

void callback(lua_State* L, lua_Debug* debugInfo) {
    console->breakpoint(debugInfo);
}

LuaDebuggerConsole::LuaDebuggerConsole() {
    console = this;
}

LuaDebuggerConsole::~LuaDebuggerConsole() {
}

void LuaDebuggerConsole::startConsole(LuaDebugger* _debugger) {
    debugger = _debugger;
    debugger->setCallback(&callback);
}

void LuaDebuggerConsole::stopConsole() {
}

void LuaDebuggerConsole::breakpoint(lua_Debug* debugInfo) {
    cout << "breakpoint reached. line: " << debugInfo->currentline << endl;
    string* command;
    do {
        command = getCommand();
        if (command->compare("get") == 0) {
            string* stack = debugger->getStack(debugInfo);
        } else if (command->compare("setbrk") == 0) {
            cout << "setbrk" << endl;
        } else if (command->compare("get2") == 0) {
            debugger->getStack2(debugInfo);
        }
    } while (command->compare("cont") != 0);

}

string* LuaDebuggerConsole::getCommand() {
    cout << "> ";
    string* command = new string();
    cin >> *command;
    return command;
}