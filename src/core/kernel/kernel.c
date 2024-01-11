#include "kernel.h"

void create_pointer_object(lua_State* L, void* pointer) {
    lua_pushinteger(L, (long long) pointer);
}

int l_require(lua_State *L) {
    const char* str = luaL_checkstring(L, 1);

    run_script(str);

    return 0;
}

int l_wait_for_vblank(lua_State *L) {
    platform_wait_vblank();
    return 0;
}

int l_get_vram_pointer(lua_State *L) {
    create_pointer_object(L, os.vram);
    return 1;
}

int l_get_key(lua_State *L) {
    long long keyCode = luaL_checknumber(L, 1);
    long long result = platform_get_key(keyCode);

    lua_pushinteger(L, (long long) result);

    return 1;
}

int l_dereference_pointer_u8_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned char*) ((void*) pointer)) = value & BIT_MASK_8U;
    return 0;
}

int l_dereference_pointer_u16_left(lua_State *L) {
    double pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned short*) ((void*) (long long) pointer)) = value & BIT_MASK_16U;
    return 0;
}

int l_dereference_pointer_u32_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned int*) ((void*) pointer)) = value & BIT_MASK_32U;
    return 0;
}

int l_dereference_pointer_u64_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned long long*) ((void*) pointer)) = value & BIT_MASK_64U;
    return 0;
}

int l_dereference_pointer_u8_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & BIT_MASK_8U;
    lua_pushinteger(L, value);
    return 1;
}

int l_dereference_pointer_u16_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & BIT_MASK_16U;
    lua_pushinteger(L, value);
    return 1;
}

int l_dereference_pointer_u32_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & BIT_MASK_32U;
    lua_pushinteger(L, value);
    return 1;
}

int l_dereference_pointer_u64_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & BIT_MASK_64U;
    lua_pushinteger(L, value);
    return 1;
}



void setup_kernel_lua_interface(LuaVM* vm) {
    lua_newtable(vm->lua_state);  /* ==> stack: ..., {} */
    {
        lua_pushliteral(vm->lua_state, "gfx" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm->lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral(vm->lua_state, "get_raw_vram_pointer" );
            lua_pushcfunction(vm->lua_state, l_get_vram_pointer);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "wait_for_vblank" );
            lua_pushcfunction(vm->lua_state, l_wait_for_vblank);
            lua_settable(vm->lua_state, -3);
        }

        lua_settable( vm->lua_state, -3 ); /* ==> stack: ..., {} */
    }
    {
        lua_pushliteral(vm->lua_state, "lua" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm->lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral(vm->lua_state, "require" );
            lua_pushcfunction(vm->lua_state, l_require);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "get_key" );
            lua_pushcfunction(vm->lua_state, l_get_key);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u8_left" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u8_left);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u16_left" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u16_left);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u32_left" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u32_left);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u64_left" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u64_left);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u8_right" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u8_right);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u16_right" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u16_right);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u32_right" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u32_right);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u64_right" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u64_right);
            lua_settable(vm->lua_state, -3);
        }

        lua_settable( vm->lua_state, -3 ); /* ==> stack: ..., {} */
    }
    lua_setglobal(vm->lua_state, "kernel" ); /* ==> stack: ... */
}

/*
void dir_list(void) {
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        perror("opendir");
        return;
    }

    int num_entries = 0;

    while (1) {
        struct dirent *cur = readdir(dirp);
        if (cur == NULL)
            break;

        if (strlen(cur->d_name) == 0)
            break;

        num_entries++;

        // Only print up to 10 entries
        if (num_entries < 10) {
            int index = telldir(dirp);
            // printf("%d - %s%s\n", index, cur->d_name,
            //    (cur->d_type == DT_DIR) ? "/" : " ");
        } else if (num_entries == 10) {
            // printf("[...]\n");
        }
    }

    closedir(dirp);

    // printf("\nNum entries: %d\n", num_entries);
}
*/
