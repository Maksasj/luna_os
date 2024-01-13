#ifndef LUNA_OS_KERNEL_FUNCTIONS_C_GFX_H
#define LUNA_OS_KERNEL_FUNCTIONS_C_GFX_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int l_get_vram_pointer(lua_State *L);
int l_get_vmap_pointer(lua_State *L);

int l_wait_for_vblank(lua_State *L);

#endif