#include "c_memory.h"

int l_malloc(lua_State *L) {
    unsigned long long size = luaL_checknumber(L, 1);
    void* ptr = malloc(size);
    printf("Allocated memory at %llu with size %llu \n", ptr, size);

    lua_pushinteger(L, (long long) ptr);

    return 1;
}

int l_free(lua_State *L) {
    void* ptr = (void*) (unsigned long long) luaL_checknumber(L, 1);
    printf("Freeing memory segment at %llu \n", ptr);

    free(ptr);
    return 0;
}

int l_dma_copy(lua_State *L) {
    void* src = (void*) (long long) luaL_checknumber(L, 1);
    void* dst = (void*) (long long) luaL_checknumber(L, 2);
    long long size = luaL_checknumber(L, 3);

    platform_memcpy(src, dst, size);

    return 0;
}