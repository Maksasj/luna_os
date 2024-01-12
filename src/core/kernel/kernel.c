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

/*
void dir_list(void) {
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        perror("opendir");
        return;
    }

    int num_entries = 0;

    while (1) {
        struct dirent *cur = readdir(dirp);
        if (cur == NULL)
            break;

        if (strlen(cur->d_name) == 0)
            break;

        num_entries++;

        // Only print up to 10 entries
        if (num_entries < 10) {
            int index = telldir(dirp);
            // printf("%d - %s%s\n", index, cur->d_name,
            //    (cur->d_type == DT_DIR) ? "/" : " ");
        } else if (num_entries == 10) {
            // printf("[...]\n");
        }
    }

    closedir(dirp);

    // printf("\nNum entries: %d\n", num_entries);
}
*/
