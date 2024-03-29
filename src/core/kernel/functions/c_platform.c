#include "c_platform.h"

#include "../../luna_os.h"

int l_get_key(lua_State *L) {
    long long keyCode = luaL_checknumber(L, 1);
    long long result = p_get_key(keyCode);

    lua_pushinteger(L, (long long) result);

    return 1;
}

int l_platform(lua_State *L) {
    lua_pushinteger(L, (long long) p_get_platform());

    return 1;
}