#include "lua.h"
#include "lauxlib.h"

static int l_add(lua_State* L) {
    double a = luaL_checknumber(L, 1);
    double b = luaL_checknumber(L, 2);
    lua_pushnumber(L, a + b);
    return 1;
}

static int l_num_threads(lua_State* L) {
    lua_pushinteger(L, 4);
    return 1;
}

// TODO: Make Multithreaded
static int l_run(lua_State* L) {
    luaL_checktype(L, 1, LUA_TFUNCTION);
    luaL_checktype(L, 2, LUA_TTABLE);

    lua_newtable(L); /* result table */
    int res_idx = lua_gettop(L);
    int n = (int)luaL_len(L, 2);

    for (int i = 1; i <= n; i++) {
        lua_geti(L, 2, i); /* push args table */
        int args_t_idx = lua_gettop(L);
        int args_n = (int)luaL_len(L, args_t_idx);

        lua_pushvalue(L, 1); /* push function */
        for (int j = 1; j <= args_n; j++) {
            lua_geti(L, args_t_idx, j); /* push arg */
        }

        lua_call(L, args_n, 1);
        lua_seti(L, res_idx, i); /* store result */
        lua_pop(L, 1); /* pop args table */
    }
    return 1;
}

static const luaL_Reg threadinglib[] = {
    {"add", l_add},
    {"run", l_run},
    {"num_threads", l_num_threads},
    {NULL, NULL}
};

int luaopen_threading(lua_State* L) {
    luaL_newlib(L, threadinglib);
    return 1;
}
