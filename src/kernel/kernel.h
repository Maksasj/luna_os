#ifndef LUNA_OS_KERNEL_H
#define LUNA_OS_KERNEL_H

#include "../luna_os.h"
#include "../lua_vm.h"

struct Package {

};

static int l_test_gfx(lua_State *L) {
    for (int y = 0; y < 192; y++) {
        for (int x = 0; x < 256; x++) {
            os.vram0[x + (y << 8)] = ARGB16(1, 0, 31, 0);
            os.vram1[x + (y << 8)] = ARGB16(1, 31, 0, 0);
        }
    }

    return 0;
}

static int l_wait_for_vblank(lua_State *L) {
    swiWaitForVBlank();

    return 0;
}

void setup_kernel_lua_interface(LuaVM* vm) {
  lua_newtable(vm->lua_state);  /* ==> stack: ..., {} */
    {
        lua_pushliteral(vm->lua_state, "gfx" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm->lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral(vm->lua_state, "test_gfx" );
            lua_pushcfunction(vm->lua_state, l_test_gfx);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "wait_for_vblank" );
            lua_pushcfunction(vm->lua_state, l_wait_for_vblank);
            lua_settable(vm->lua_state, -3);
        }

        lua_settable( vm->lua_state, -3 ); /* ==> stack: ..., {} */
    }
    lua_setglobal(vm->lua_state, "kernel" ); /* ==> stack: ... */
}

#endif