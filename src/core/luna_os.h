#ifndef LUNA_OS_H
#define LUNA_OS_H

#include "lua_vm/lua_vm.h"

typedef struct LunaOS {
    // Scren buffers
    unsigned short* vram0;
    unsigned short* vram1;

    // Lua virtual machine
    LuaVM vm;
} LunaOS;

extern LunaOS os;

#endif