#include "c_platform.h"

#include "../../luna_os.h"

int l_require(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);

    run_script(str);

    return 0;
}

int l_get_key(lua_State *L) {
    long long keyCode = luaL_checknumber(L, 1);
    long long result = platform_get_key(keyCode);

    lua_pushinteger(L, (long long) result);

    return 1;
}

int l_platform(lua_State *L) {
    lua_pushinteger(L, (long long) platform_get_platform());

    return 1;
}