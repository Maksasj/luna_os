#ifndef LUNA_OS_KERNEL_FUNCTIONS_C_MEMORY_H
#define LUNA_OS_KERNEL_FUNCTIONS_C_MEMORY_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int l_malloc(lua_State *L);
int l_free(lua_State *L);
int l_dma_copy(lua_State *L);
int l_get_key(lua_State *L);

#endif