#ifndef LUNA_OS_KERNEL_FUNCTIONS_C_POINTER_H
#define LUNA_OS_KERNEL_FUNCTIONS_C_POINTER_H

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#define BIT_MASK_8U     0xFF
#define BIT_MASK_16U    0xFFFF
#define BIT_MASK_32U    0xFFFFFFFF
#define BIT_MASK_64U    0xFFFFFFFFFFFFFFFF

int l_dereference_pointer_u8_left(lua_State *L);
int l_dereference_pointer_u16_left(lua_State *L);
int l_dereference_pointer_u32_left(lua_State *L);
int l_dereference_pointer_u64_left(lua_State *L);

int l_dereference_pointer_u8_right(lua_State *L);
int l_dereference_pointer_u16_right(lua_State *L);
int l_dereference_pointer_u32_right(lua_State *L);
int l_dereference_pointer_u64_right(lua_State *L);

#endif