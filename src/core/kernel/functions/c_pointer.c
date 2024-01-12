#include "c_pointer.h"

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