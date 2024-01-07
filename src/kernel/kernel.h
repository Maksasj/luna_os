#ifndef LUNA_OS_KERNEL_H
#define LUNA_OS_KERNEL_H

#include "../luna_os.h"
#include "../lua_vm.h"

struct Package {

};

static int l_test_gfx(lua_State *L) {
    for (int y = 0; y < 192; y++) {
        for (int x = 0; x < 256; x++) {
            os.vram0[x + (y << 8)] = ARGB16(1, 0, 31, 0);
            os.vram1[x + (y << 8)] = ARGB16(1, 31, 0, 0);
        }
    }

    return 0;
}

static int l_wait_for_vblank(lua_State *L) {
    swiWaitForVBlank();

    return 0;
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

void setup_kernel_lua_interface(LuaVM* vm) {
  lua_newtable(vm->lua_state);  /* ==> stack: ..., {} */
    {
        lua_pushliteral(vm->lua_state, "gfx" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm->lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral(vm->lua_state, "test_gfx" );
            lua_pushcfunction(vm->lua_state, l_test_gfx);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "wait_for_vblank" );
            lua_pushcfunction(vm->lua_state, l_wait_for_vblank);
            lua_settable(vm->lua_state, -3);
        }

        lua_settable( vm->lua_state, -3 ); /* ==> stack: ..., {} */
    }
    lua_setglobal(vm->lua_state, "kernel" ); /* ==> stack: ... */
}

#endif