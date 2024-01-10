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

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        fire_error("Failed to allocate memory for lua code\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = (char*)malloc(file_size + 1);

    if (content == NULL) {
        fclose(file);
        fire_error("Failed to allocate memory for lua code\n");
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';

    fclose(file);

    return content;
}

void run_script(const char* entryPointPath) {
    char* lua_code = read_file(entryPointPath);

    int luaRes = luaL_dostring(os.vm.lua_state, lua_code);

    if(luaRes)
        fire_error(lua_tostring(os.vm.lua_state, -1));

    free(lua_code);
}