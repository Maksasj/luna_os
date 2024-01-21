#include "c_file.h"

int l_fopen(lua_State *L) {
    const char* path = luaL_checkstring(L, 1);
    const char* mode = luaL_checkstring(L, 2);

    FILE* file = fopen(path, mode);

    lua_pushinteger(L, (long long) file);

    return 1;
}

int l_fclose(lua_State *L) {
    void* file = (void*) (unsigned long long) luaL_checknumber(L, 1);
    fclose(file);
    return 0;
}
