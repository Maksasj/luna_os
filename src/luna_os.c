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
            printf("%d - %s%s\n", index, cur->d_name,
                (cur->d_type == DT_DIR) ? "/" : " ");
        } else if (num_entries == 10) {
            printf("[...]\n");
        }
    }

    closedir(dirp);

    printf("\nNum entries: %d\n", num_entries);
}

void open_bush_package() {
    char input_buffer[1024] = { '\0' };
    FILE *f = fopen("packages/bush/package.lua", "r");
    int input_size = fread(input_buffer, 1, 1024, f);

    LuaVM vm;
    start_lua_vm(&vm);

    int res = luaL_dostring(L, input_buffer);

    terminate_lua_vm(&vm);
}

int main(int argc, char *argv[]) {
    consoleDemoInit();

    printf("\x1b[2J"); // Clear console

    printf("DLDI name:\n%s\n\n", io_dldi_data->friendlyName);
    printf("DSi mode: %d\n\n", isDSiMode());

    printf("\n");
    printf("Press START to exit to loader\n");

    bool init_ok = fatInitDefault();
    if (!init_ok) {
        perror("fatInitDefault()");
    } else {
        char *cwd = getcwd(NULL, 0);
        printf("Current dir: %s\n\n", cwd);
        free(cwd);

        open_bush_package();
    }

    while (1) {
        swiWaitForVBlank();

        scanKeys();

        uint32_t keys_down = keysDown();
        if (keys_down & KEY_START)
            break;
    }

    return 0;
}