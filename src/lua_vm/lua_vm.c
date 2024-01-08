#include "lua_vm.h"

#include "../luna_os.h"

void start_lua_vm(LuaVM* vm) {
	vm->lua_state = luaL_newstate();
	// luaL_openlibsCustom(vm->lua_state);
}

void terminate_lua_vm(LuaVM* vm) {
    lua_close(vm->lua_state);
}

void error_lua_vm() {
    // For now entire screen will just blink
    while(1) {
        for (int y = 0; y < 192; y++) {
            for (int x = 0; x < 256; x++) {
                os.vram0[x + (y << 8)] = ARGB16(1, rand() % 31, rand() % 31, rand() % 31);
                os.vram1[x + (y << 8)] = ARGB16(1, rand() % 31, rand() % 31, rand() % 31);
            }
        }

        swiWaitForVBlank();
    }
}
