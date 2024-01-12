#include "c_gfx.h"

#include "../../luna_os.h"

int l_wait_for_vblank(lua_State *L) {
    p_wait_vblank();
    return 0;
}

int l_get_vram0_pointer(lua_State *L) {
    lua_pushinteger(L, (long long) os.vram0);
    return 1;
}

int l_get_vram1_pointer(lua_State *L) {
    lua_pushinteger(L, (long long) os.vram1);
    return 1;
}

int l_get_vmap_pointer(lua_State *L) {
    lua_pushinteger(L, (long long) os.vmap);
    return 1;
}