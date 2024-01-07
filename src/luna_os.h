#ifndef LUNA_OS_H
#define LUNA_OS_H

#include <nds.h>

#include "lua_vm.h"

typedef struct LunaOS {
    // Scren buffers
    u16* vram0;
    u16* vram1;

    // Lua virtual machine
    LuaVM vm;
} LunaOS;

extern LunaOS os;

#endif