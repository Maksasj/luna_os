#ifndef LUNA_OS_LUA_VM_H
#define LUNA_OS_LUA_VM_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

typedef struct LuaVM {
    lua_State* lua_state;
} LuaVM;

void start_lua_vm(LuaVM* vm) {
    vm->lua_state = luaL_newstate();
    luaL_openlibs(vm->lua_state);
}

void terminate_lua_vm(LuaVM* vm) {
    lua_close(vm->lua_state);
}

/*
static int l_sin(lua_State *L) {
    // double d = lua_tonumber(L, 1); get argument
    // lua_pushnumber(L, sin(d));   push result

    printf("poggers %f!\n", d);

    return 0;  number of results
}
*/

#endif