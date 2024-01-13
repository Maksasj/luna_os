#include "c_gfx.h"

#include "../../luna_os.h"

int l_wait_for_vblank(lua_State *L) {
    p_wait_vblank();
    return 0;
}

int l_get_vram_pointer(lua_State *L) {
    lua_pushinteger(L, (long long) os.vram);
    return 1;
}

int l_get_vmap_pointer(lua_State *L) {
    lua_pushinteger(L, (long long) os.vmap);
    return 1;
}