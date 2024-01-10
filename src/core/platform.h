#ifndef LUNA_OS_PLATFORM_H
#define LUNA_OS_PLATFORM_H

#include "luna_os.h"

#define ARGB16(a, r, g, b)  (((a) << 15) | (r) | ((g) << 5) | ((b) << 10))

void setup_gfx(LunaOS* os_instance);

void setup_fat();

void setup_platform(LunaOS* os_instance);

void fire_error(const char* error_message);

#endif