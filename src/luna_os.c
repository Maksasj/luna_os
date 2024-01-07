#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#include <dirent.h>

#include <errno.h>
#include <stdio.h>

#include <fatfs.h>
#include <nds.h>

#include <nds/arm9/dldi.h>

int main(int argc, char *argv[]) {
    consoleDemoInit();

    printf("\x1b[2J"); // Clear console

    printf("DLDI name:\n%s\n\n", io_dldi_data->friendlyName);
    printf("DSi mode: %d\n\n", isDSiMode());

    printf("\n");
    printf("Press START to exit to loader\n");

    lua_State* L;

    L = luaL_newstate();

    luaL_openlibs(L);

    luaL_dostring(L, "for x = 1, 5 do print(x) end");

    lua_close(L);

    while (1) {
        swiWaitForVBlank();

        scanKeys();

        uint32_t keys_down = keysDown();
        if (keys_down & KEY_START)
            break;
    }

    return 0;
}