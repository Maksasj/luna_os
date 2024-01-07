#include "platform.h"
#include "kernel/kernel.h"
#include "lua_vm.h"

LunaOS os = {};

void run_package(const char* entryPointPath) {
    char input_buffer[1024] = { '\0' };
    FILE *f = fopen(entryPointPath, "r");
    int input_size = fread(input_buffer, 1, 1024, f);

    int res = luaL_dostring(os.vm.lua_state, input_buffer);
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
