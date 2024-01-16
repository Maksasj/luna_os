#ifndef LUNA_OS_KERNEL_FUNCTIONS_PLATFORM_LUA_H
#define LUNA_OS_KERNEL_FUNCTIONS_PLATFORM_LUA_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int l_get_key(lua_State *L);
int l_platform(lua_State *L);

#endif