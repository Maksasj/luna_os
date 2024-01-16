#ifndef LUNA_OS_KERNEL_H
#define LUNA_OS_KERNEL_H

#include "../luna_os.h"
#include "../lua_vm/lua_vm.h"

#include "../platform.h"

#include "functions/c_pointer.h"
#include "functions/c_memory.h"
#include "functions/c_platform.h"
#include "functions/c_gfx.h"
#include "functions/c_dirent.h"

typedef struct LuaKernelFunction {
    const char* name;
    void* function;
} LuaKernelFunction;

static LuaKernelFunction lua_kernel_functions[] = {
    // gfx
    { "_get_raw_vram_pointer", l_get_vram_pointer },
    { "_get_raw_vmap_pointer", l_get_vmap_pointer },
    { "_wait_for_vblank", l_wait_for_vblank },
    
    // platform
    { "_get_key", l_get_key },
    { "_platform", l_platform },

    // memory
    { "_malloc", l_malloc },
    { "_free", l_free },
    { "_dma_copy", l_dma_copy },

    // dirent
    { "_opendir", l_opendir },
    { "_readdir", l_readdir },
    { "_telldir", l_telldir },
    { "_closedir", l_closedir },
    { "_dirent_get_ino", l_dirent_get_ino},
    { "_dirent_get_reclen", l_dirent_get_reclen},
    { "_dirent_get_name", l_dirent_get_name},
    
    // pointer
    { "_dereference_pointer_u8_left", l_dereference_pointer_u8_left }, 
    { "_dereference_pointer_u16_left", l_dereference_pointer_u16_left }, 
    { "_dereference_pointer_u32_left", l_dereference_pointer_u32_left }, 
    { "_dereference_pointer_u64_left", l_dereference_pointer_u64_left }, 
    { "_dereference_pointer_u8_right", l_dereference_pointer_u8_right }, 
    { "_dereference_pointer_u16_right", l_dereference_pointer_u16_right }, 
    { "_dereference_pointer_u32_right", l_dereference_pointer_u32_right }, 
    { "_dereference_pointer_u64_right", l_dereference_pointer_u64_right }
};

void setup_kernel_lua_interface(LuaVM* vm);

#endif