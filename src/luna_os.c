#include "platform.h"
#include "kernel/kernel.h"
#include "lua_vm.h"

LunaOS os = {};

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

void run_package(const char* entryPointPath) {
    char input_buffer[1024] = { '\0' };
    FILE *f = fopen(entryPointPath, "r");
    int input_size = fread(input_buffer, 1, 1024, f);

    int res = luaL_dostring(os.vm.lua_state, input_buffer);
}

void setup_gfx() {
	videoSetMode(MODE_5_2D); 
    videoSetModeSub(MODE_5_2D);

	int bg0 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	int bg1 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	os.vram0 = (u16*) bgGetGfxPtr(bg0);
	os.vram1 = (u16*) bgGetGfxPtr(bg1);
}

void setup_fat() {
    bool init_ok = fatInitDefault();
    if (!init_ok) {
        perror("fatInitDefault()");
    } else {
        char *cwd = getcwd(NULL, 0);
        // printf("Current dir: %s\n\n", cwd);
        free(cwd);
    }
}

int main(int argc, char *argv[]) {
    // Setup gfx
    setup_gfx();

    // Setup file system
    setup_fat();

    // Setup lua virtual machine and start boot lua package
    start_lua_vm(&os.vm);
    setup_kernel_lua_interface(&os.vm);

    run_package("packages/bush/main.lua");

    // terminate and cleanup
    terminate_lua_vm(&os.vm);

    return 0;
}
