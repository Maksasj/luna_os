#ifndef LUNA_OS_KERNEL_H
#define LUNA_OS_KERNEL_H

#include "../luna_os.h"
#include "../lua_vm/lua_vm.h"

#include "../platform.h"

#define BIT_MASK_8U     0xFF
#define BIT_MASK_16U    0xFFFF
#define BIT_MASK_32U    0xFFFFFFFF
#define BIT_MASK_64U    0xFFFFFFFFFFFFFFFF

void create_pointer_object(lua_State* L, void* pointer);

static int l_require(lua_State *L);

static int l_wait_for_vblank(lua_State *L);

static int l_get_vram_pointer(lua_State *L);

static int l_dereference_pointer_u8_left(lua_State *L);
static int l_dereference_pointer_u16_left(lua_State *L);
static int l_dereference_pointer_u32_left(lua_State *L);
static int l_dereference_pointer_u64_left(lua_State *L);

static int l_dereference_pointer_u8_right(lua_State *L);
static int l_dereference_pointer_u16_right(lua_State *L);
static int l_dereference_pointer_u32_right(lua_State *L);
static int l_dereference_pointer_u64_right(lua_State *L);

void setup_kernel_lua_interface(LuaVM* vm);

#endif