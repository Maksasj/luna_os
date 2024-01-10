#ifndef LUNA_OS_LUA_VM_H
#define LUNA_OS_LUA_VM_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

typedef struct LuaVM {
    lua_State* lua_state;
} LuaVM;

void start_lua_vm(LuaVM* vm);

void terminate_lua_vm(LuaVM* vm);

void error_lua_vm();

void run_script(const char* entryPointPath);

#endif