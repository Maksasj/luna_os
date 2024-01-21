#include "c_dirent.h"

int l_opendir(lua_State *L) {
    const char* path = luaL_checkstring(L, 1);
    void* dirp = opendir(path);
    lua_pushinteger(L, (long long) dirp);

    return 1;
}

int l_readdir(lua_State *L) {
    void* dirp = (void*) (unsigned long long) luaL_checknumber(L, 1);
    struct dirent *cur = readdir(dirp);
    lua_pushinteger(L, (long long) cur);
    return 1;
}

int l_telldir(lua_State *L) {
    void* dirp = (void*) (unsigned long long) luaL_checknumber(L, 1);
    int index = telldir(dirp);
    lua_pushinteger(L, (long long) index);
    return 1;
}

int l_closedir(lua_State *L) {
    void* dirp = (void*) (unsigned long long) luaL_checknumber(L, 1);
    closedir(dirp);
    return 0;
}

int l_dirent_get_ino(lua_State *L) {
    struct dirent *cur = (struct dirent*) (unsigned long long) luaL_checknumber(L, 1);
    lua_pushinteger(L, (long long) cur->d_ino);
    return 1;
}

int l_dirent_get_reclen(lua_State *L) {
    struct dirent *cur = (struct dirent*) (unsigned long long) luaL_checknumber(L, 1);
    lua_pushinteger(L, (long long) cur->d_reclen);
    return 1;
}

int l_dirent_get_name(lua_State *L) {
    struct dirent *cur = (struct dirent*) (unsigned long long) luaL_checknumber(L, 1);
    lua_pushstring(L, cur->d_name);
    return 1;
}
