#include "platform.h"

#include "kernel/kernel.h"
#include "lua_vm/lua_vm.h"

LunaOS os = {};

void run_package(const char* entryPointPath) {
    int res = luaL_dofile(os.vm.lua_state, entryPointPath);

    if(res)
        error_lua_vm();
}

int main(int argc, char *argv[]) {
    // Setup platform
    setup_platform(&os);

    // Setup lua virtual machine and start boot lua package
    start_lua_vm(&os.vm);
    setup_kernel_lua_interface(&os.vm);

    run_package("packages/bush/main.lua");

    // terminate and cleanup
    terminate_lua_vm(&os.vm);

    return 0;
}
