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

void run_script(const char* entryPointPath) {
    int luaRes = luaL_dofile(os.vm.lua_state, entryPointPath);

    if(luaRes)
        p_fire_error(lua_tostring(os.vm.lua_state, -1));
}