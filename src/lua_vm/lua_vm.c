#include "lua_vm.h"

#include "../luna_os.h"
#include "../platform.h"

void start_lua_vm(LuaVM* vm) {
	vm->lua_state = luaL_newstate();
	luaL_openlibs(vm->lua_state);
}

void terminate_lua_vm(LuaVM* vm) {
    lua_close(vm->lua_state);
}

void error_lua_vm() {
    // For now entire screen will just blink
    while(1) {
        for (int y = 0; y < 192; y++) {
            for (int x = 0; x < 256; x++) {
                os.vram0[x + (y << 8)] = ARGB16(1, rand() % 31, 0, 0);
                os.vram1[x + (y << 8)] = ARGB16(1, rand() % 31, 0, 0);
            }
        }

        swiWaitForVBlank();
    }
}

void run_script(const char* entryPointPath) {
    FILE *file = fopen(entryPointPath, "r");
    fseek(file, 0L, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* lua_code = (char*) malloc(file_size * sizeof(char));

    fread(lua_code, sizeof(char), file_size, file);

    int luaRes = luaL_dostring(os.vm.lua_state, lua_code);

    free(lua_code);
    if(luaRes)
        error_lua_vm();
}