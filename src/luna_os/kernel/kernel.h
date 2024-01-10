#ifndef LUNA_OS_KERNEL_H
#define LUNA_OS_KERNEL_H

#include "../luna_os.h"
#include "../lua_vm/lua_vm.h"

struct Package {

};

static int l_test_gfx(lua_State *L);

static int l_require(lua_State *L);

static int l_wait_for_vblank(lua_State *L);

void setup_kernel_lua_interface(LuaVM* vm);

#endif