#ifndef LUNA_OS_LUA_VM_H
#define LUNA_OS_LUA_VM_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

struct LuaVM {
    lua_State* lua_state;
};

void start_lua_vm(LuaVM* vm) {
    vm->lua_state = luaL_newstate();
    luaL_openlibs(vm->lua_state);
}

void terminate_lua_vm(LuaVM* vm) {
    lua_close(vm->lua_state);
}

#endif