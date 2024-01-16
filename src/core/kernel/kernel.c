#include "kernel.h"

void setup_kernel_lua_interface(LuaVM* vm) {
    lua_newtable(vm->lua_state);  /* ==> stack: ..., {} */

    int lua_kernel_functions_size = sizeof(lua_kernel_functions) / sizeof(LuaKernelFunction); 
    for(int i = 0; i < lua_kernel_functions_size; ++i) {
        LuaKernelFunction function = lua_kernel_functions[i];

        lua_pushstring(vm->lua_state, function.name);
        lua_pushcfunction(vm->lua_state, function.function);
        lua_settable(vm->lua_state, -3);
    }
   
    lua_setglobal(vm->lua_state, "kernel" ); /* ==> stack: ... */
}
