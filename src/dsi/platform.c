// For now just dsi specific
#include <sys/dirent.h>

#include <errno.h>
#include <stdio.h>

#include <fatfs.h>
#include <nds.h>

#include <nds/arm9/dldi.h>

#include "platform.h"

void p_setup_gfx(LunaOS* os_instance) {
    // vramSetMainBanks(VRAM_A_MAIN_BG | VRAM_C_SUB_BG);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
}

void p_setup_fat() {
    bool init_ok = fatInitDefault();

    if (!init_ok) {
        p_fire_error("Failed to initialize fat library");
    } else {
        //  char *cwd = getcwd(NULL, 0);
        // printf("Current dir: %s\n\n", cwd);
        // free(cwd);
    }
}

void p_setup(LunaOS* os_instance) {
    p_setup_gfx(os_instance);
    p_setup_fat();
}

void p_fire_error(const char* error_message) {
    consoleDemoInit();

    printf("\x1b[28DLuna lua VM error: %s", error_message);

    while(1) {
        swiWaitForVBlank();
        scanKeys();

        int keys = keysDown();

        if(keys & KEY_START) break;
    }
}

void p_wait_vblank() {
    scanKeys();
    swiWaitForVBlank();
}

int p_get_key(long long keyCode) {
    // unsigned short buttons = keysHeld();
    unsigned short buttons = ~(*(unsigned short*) 0x04000130);

    if (keyCode == 0) {
        return buttons & 0x0001;
    } else if (keyCode == 1) {
        return buttons & 0x0002;
    } else if (keyCode == 2) {
        return buttons & 0x0004;
    } else if (keyCode == 3) {
        return buttons & 0x0008;
    } else if (keyCode == 4) {
        return buttons & 0x0010;
    } else if (keyCode == 5) {
        return buttons & 0x0020;
    } else if (keyCode == 6) {
        return buttons & 0x0040;
    } else if (keyCode == 7) {
        return buttons & 0x0080;
    } else if (keyCode == 8) {
        return buttons & 0x0100;
    } else if (keyCode == 9) {
        return buttons & 0x0200;
    } else if (keyCode == 10) {
        return buttons & KEY_X;
    } else if (keyCode == 11) {
        return buttons & KEY_Y;
    }
}

void p_memcpy(void* src, void* dst, unsigned long size) {
    dmaCopy(src, dst, size);
}

Platform p_get_platform() {
    return DSI;
}