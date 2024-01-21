#ifndef LUNA_OS_KERNEL_FUNCTIONS_DIRENT_H
#define LUNA_OS_KERNEL_FUNCTIONS_DIRENT_H

#include <dirent.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int l_opendir(lua_State *L);
int l_readdir(lua_State *L);
int l_telldir(lua_State *L);
int l_closedir(lua_State *L);

int l_dirent_get_ino(lua_State *L);
int l_dirent_get_reclen(lua_State *L);
int l_dirent_get_name(lua_State *L);

#endif