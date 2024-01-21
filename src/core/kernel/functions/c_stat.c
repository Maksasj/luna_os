#include "c_stat.h"

int l_stat(lua_State *L) {
    void* path = (void*) (unsigned long long) luaL_checkstring(L, 1);
    void* buf = (void*) (unsigned long long) luaL_checknumber(L, 2);

    long long ret = stat(path, buf);

    lua_pushinteger(L, ret);
    return 1;
}

int l_stat_st_dev(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_dev;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_ino(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_ino;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_mode(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_mode;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_nlink(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_nlink;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_uid(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_uid;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_gid(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_gid;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_rdev(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_rdev;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_size(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_size;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_atime(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_atime;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_mtime(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_mtime;

    lua_pushinteger(L, value);
    return 1;
}

int l_stat_st_ctime(lua_State *L) {
    struct stat* stat = (struct stat*) (unsigned long long) luaL_checknumber(L, 1);
    unsigned long long value = stat->st_ctime;

    lua_pushinteger(L, value);
    return 1;
}