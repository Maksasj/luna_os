#include "platform.h"
#include "kernel.h"
#include "lua_vm.h"

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

u16* vram0;
u16* vram1;

static int l_some(lua_State *L) {
    // double d = lua_tonumber(L, 1); get argument
    // lua_pushnumber(L, sin(d));   push result

        for (int y = 0; y < 192; y++) {
            for (int x = 0; x < 256; x++) {
                vram0[x + (y << 8)] = ARGB16(1, 0, 31, 0);
                vram1[x + (y << 8)] = ARGB16(1, 31, 0, 0);
            }
        }

    return 0;
}







void open_bush_package() {
    char input_buffer[1024] = { '\0' };
    FILE *f = fopen("packages/bush/main.lua", "r");
    int input_size = fread(input_buffer, 1, 1024, f);

    LuaVM vm;
    start_lua_vm(&vm);

    // lua_pushcfunction(vm.lua_state, l_sin);
    // lua_setglobal(vm.lua_state, "printmore");











    lua_newtable( vm.lua_state );  /* ==> stack: ..., {} */
    {
        lua_pushliteral( vm.lua_state, "gfx" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm.lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral( vm.lua_state, "some" );
            lua_pushcfunction(vm.lua_state, l_some);
            lua_settable(vm.lua_state, -3);
        }

        lua_settable( vm.lua_state, -3 ); /* ==> stack: ..., {} */
    }
    lua_setglobal(vm.lua_state, "kernel" ); /* ==> stack: ... */





    int res = luaL_dostring(vm.lua_state, input_buffer);

    terminate_lua_vm(&vm);
}

void run_another_stuf() {
    bool init_ok = fatInitDefault();
    if (!init_ok) {
        perror("fatInitDefault()");
    } else {
        char *cwd = getcwd(NULL, 0);
        // printf("Current dir: %s\n\n", cwd);
        free(cwd);

        open_bush_package();
    }
}

int main(int argc, char *argv[]) {
	videoSetMode(MODE_5_2D); 
    videoSetModeSub(MODE_5_2D);

	int bg0 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	int bg1 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	vram0 = (u16*) bgGetGfxPtr(bg0);
	vram1 = (u16*) bgGetGfxPtr(bg1);

    run_another_stuf();

	while(1){
        /*
        for (int y = 0; y < 192; y++) {
            for (int x = 0; x < 256; x++) {
                vram0[x + (y << 8)] = ARGB16(1, 0, 31, 0);
                vram1[x + (y << 8)] = ARGB16(1, 31, 0, 0);
            }
        }
        */

		swiWaitForVBlank();

		scanKeys();
		if(keysDown() & KEY_START)
            break;
	}

    return 0;
}
