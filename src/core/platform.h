#ifndef LUNA_OS_PLATFORM_H
#define LUNA_OS_PLATFORM_H

#include "luna_os.h"

typedef enum Platform {
    DSI = 0,
    DESKTOP = 1
} Platform;

void setup_gfx(LunaOS* os_instance);

void setup_fat();

void setup_platform(LunaOS* os_instance);

void platform_wait_vblank();

void platform_fire_error(const char* error_message);

int platform_get_key(long long keyCode);

void platform_memcpy(void* src, void* dst, unsigned long size);

Platform platform_get_platform();

#endif