#ifndef LUNA_OS_PLATFORM_H
#define LUNA_OS_PLATFORM_H

#include "luna_os.h"

void setup_gfx(LunaOS* os_instance);

void setup_fat();

void setup_platform(LunaOS* os_instance);

void platform_wait_vblank();

void platform_fire_error(const char* error_message);

#endif