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

void setup_gfx(LunaOS* os_instance);

void setup_fat();

void setup_platform(LunaOS* os_instance);

#endif