#include "platform.h"

#include "kernel/kernel.h"
#include "lua_vm/lua_vm.h"

LunaOS os = {};

int main(int argc, char *argv[]) {
    // Setup platform
    setup_platform(&os);

    // Setup lua virtual machine and start boot lua package
    start_lua_vm(&os.vm);
    setup_kernel_lua_interface(&os.vm);

    run_script("packages/bush/main.lua");

    // terminate and cleanup
    terminate_lua_vm(&os.vm);

    return 0;
}
