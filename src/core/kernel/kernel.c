#include "kernel.h"

#include <stdio.h>

#define ARGB16(a, r, g, b)  (((a) << 15) | (r) | ((g) << 5) | ((b) << 10))

static int l_test_gfx(lua_State *L) {
    int x_arg = luaL_checknumber(L, 1);
    int y_arg = luaL_checknumber(L, 2);

    os.vram0[x_arg + (y_arg << 8)] = ARGB16(1, 31, 31, 31);
    // os.vram1[x_arg + (y_arg << 8)] = ARGB16(1, 31, 31, 31);
    
    return 0;
}

static int l_require(lua_State *L) {
    char* str = luaL_checkstring(L, 1);

    run_script(str);

    return 0;
}

static int l_wait_for_vblank(lua_State *L) {
    swiWaitForVBlank();

    return 0;
}

void create_pointer_object(lua_State* L, void* pointer) {
    lua_pushinteger(L, (long long) pointer);
}

static int l_get_vram_pointer(lua_State *L) {
    create_pointer_object(L, os.vram0);
    return 1;
}

static int l_dereference_pointer_u8_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned char*) ((void*) pointer)) = value & 0xFF;
}

static int l_dereference_pointer_u16_left(lua_State *L) {
    double pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned short*) ((void*) (long long) pointer)) = value & 0xFFFF;
}

static int l_dereference_pointer_u32_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned int*) ((void*) pointer)) = value & 0xFFFFFFFF;
}

static int l_dereference_pointer_u64_left(lua_State *L) {
    long long pointer = luaL_checknumber(L, 1);
    long long value = luaL_checknumber(L, 2);
    *((unsigned long long*) ((void*) pointer)) = value & 0xFFFFFFFFFFFFFFFF;
}

static int l_dereference_pointer_u8_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & 0xFF;
    lua_pushinteger(L, value);
}

static int l_dereference_pointer_u16_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & 0xFFFF;
    lua_pushinteger(L, value);
}

static int l_dereference_pointer_u32_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & 0xFFFFFFFF;
    lua_pushinteger(L, value);
}

static int l_dereference_pointer_u64_right(lua_State *L) {
    void* pointer = (void*) ((long long) luaL_checknumber(L, 1));
    long long value = *((long long*) pointer) & 0xFFFFFFFFFFFFFFFF;
    lua_pushinteger(L, value);
}

void setup_kernel_lua_interface(LuaVM* vm) {
    lua_newtable(vm->lua_state);  /* ==> stack: ..., {} */
    {
        lua_pushliteral(vm->lua_state, "gfx" ); /* ==> stack: ..., {}, "b" */
        lua_newtable(vm->lua_state ); /* ==> stack: ..., {}, "b", {} */

        {
            lua_pushliteral(vm->lua_state, "test_gfx" );
            lua_pushcfunction(vm->lua_state, l_test_gfx);
            lua_settable(vm->lua_state, -3);
        }

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
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u64_right" );
            lua_pushcfunction(vm->lua_state, l_dereference_pointer_u16_right);
            lua_settable(vm->lua_state, -3);
        }

        {
            lua_pushliteral(vm->lua_state, "_dereference_pointer_u64_right" );
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
