#ifndef LUNA_OS_KERNEL_FUNCTIONS_STAT_H
#define LUNA_OS_KERNEL_FUNCTIONS_STAT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

/*
struct stat {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};
*/

int l_stat(lua_State *L);

int l_stat_st_dev(lua_State *L);
int l_stat_st_ino(lua_State *L);
int l_stat_st_mode(lua_State *L);
int l_stat_st_nlink(lua_State *L);
int l_stat_st_uid(lua_State *L);
int l_stat_st_gid(lua_State *L);
int l_stat_st_rdev(lua_State *L);
int l_stat_st_size(lua_State *L);
int l_stat_st_atime(lua_State *L);
int l_stat_st_mtime(lua_State *L);
int l_stat_st_ctime(lua_State *L);

#endif