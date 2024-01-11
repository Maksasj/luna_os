// For now just dsi specific
#include <sys/dirent.h>

#include <errno.h>
#include <stdio.h>

#include <fatfs.h>
#include <nds.h>

#include <nds/arm9/dldi.h>

#include "platform.h"

void setup_gfx(LunaOS* os_instance) {
	videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);

    int bg0T = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
	int bg0B = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	
	int bg1 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	os_instance->vram0 = (u16*) bgGetGfxPtr(bg0B);
    os_instance->vram1 = (u16*) bgGetGfxPtr(bg0T);

    os_instance->vmap = (u16*) bgGetMapPtr(bg0T);
}

void setup_fat() {
    bool init_ok = fatInitDefault();
    if (!init_ok) {
        platform_fire_error("Failed to initialize fat library");
    } else {
        char *cwd = getcwd(NULL, 0);
        // printf("Current dir: %s\n\n", cwd);
        free(cwd);
    }
}

void setup_platform(LunaOS* os_instance) {
    setup_gfx(os_instance);
    setup_fat();
}

void platform_fire_error(const char* error_message) {
    while(1) {
        for (int y = 0; y < 192; y++) {
            for (int x = 0; x < 256; x++) {
                os.vram0[x + (y << 8)] = ARGB16(1, rand() % 31, 0, 0);
            }
        }

        platform_wait_vblank();
    }
}

void platform_wait_vblank() {
    scanKeys();
    swiWaitForVBlank();
}

int platform_get_key(long long keyCode) {
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

void platform_memcpy(void* src, void* dst, unsigned long size) {
    dmaCopy(src, dst, size);
}
