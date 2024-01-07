#ifndef LUNA_OS_PLATFORM_H
#define LUNA_OS_PLATFORM_H

// For now just dsi specific
#include <dirent.h>

#include <errno.h>
#include <stdio.h>

#include <fatfs.h>
#include <nds.h>

#include <nds/arm9/dldi.h>

#include "luna_os.h"

void setup_gfx(LunaOS* os_instance) {
	videoSetMode(MODE_5_2D); 
    videoSetModeSub(MODE_5_2D);

	int bg0 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	int bg1 = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	os_instance->vram0 = (u16*) bgGetGfxPtr(bg0);
	os_instance->vram1 = (u16*) bgGetGfxPtr(bg1);
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

void setup_platform(LunaOS* os_instance) {
    setup_gfx(os_instance);
    setup_fat();
} 

#endif