#include "lua_vm.h"

#include "../luna_os.h"
#include "../platform.h"

#include <stdio.h>

#define ARGB16(a, r, g, b)  (((a) << 15) | (r) | ((g) << 5) | ((b) << 10))

void start_lua_vm(LuaVM* vm) {
	vm->lua_state = luaL_newstate();
	luaL_openlibs(vm->lua_state);
}

void terminate_lua_vm(LuaVM* vm) {
    lua_close(vm->lua_state);
}

void run_script(const char* entryPointPath) {
    FILE *file = fopen(entryPointPath, "rb");
    if(file == NULL)
        fire_error("Failed to open file\n");

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* lua_code = (char*) malloc(file_size * sizeof(char));
    if(lua_code == NULL)
        fire_error("Failed to allocate memory for lua code\n");

    fread(lua_code, 1, file_size, file);

    int luaRes = luaL_dostring(os.vm.lua_state, lua_code);

    free(lua_code);
    if(luaRes)
        fire_error(lua_tostring(os.vm.lua_state, -1));

    fclose(file);
}