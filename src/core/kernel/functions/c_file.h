#ifndef LUNA_OS_KERNEL_FUNCTIONS_FILE_H
#define LUNA_OS_KERNEL_FUNCTIONS_FILE_H

#include <stdio.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int l_fopen(lua_State *L);
int l_fclose(lua_State *L);

#endif