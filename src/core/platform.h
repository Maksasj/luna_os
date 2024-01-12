#ifndef LUNA_OS_PLATFORM_H
#define LUNA_OS_PLATFORM_H

#include "luna_os.h"

typedef enum Platform {
    DSI = 0,
    DESKTOP = 1
} Platform;

// setup
void p_setup_gfx(LunaOS* os_instance);
void p_setup_fat();
void p_setup(LunaOS* os_instance);

// gfx
void p_wait_vblank();

// io
int p_get_key(long long keyCode);

// memory
void p_memcpy(void* src, void* dst, unsigned long size);

// general
void p_fire_error(const char* error_message);
Platform p_get_platform();

#endif