#include "update.h"

#include <string.h>
#include <stddef.h>

#include <lauxlib.h>

#include "enums.h"

static const char* metatable_name = "lhk.Update";

int update_new(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", update_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{NULL, NULL}
};

void update_open(lua_State* L) {
	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "update");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_update* update_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

void update_push(lua_State* L, struct libhotkey_update update) {
	*(struct libhotkey_update*)lua_newuserdata(L, sizeof(struct libhotkey_update)) = update;
	luaL_setmetatable(L, metatable_name);
}

int update_new(lua_State* L) {
	struct libhotkey_update* update = lua_newuserdata(L, sizeof(struct libhotkey_update));

	update->keycode = luaL_checkinteger(L, 1);
	update->transition = transition_get(L, 2);

	luaL_setmetatable(L, metatable_name);

	return 1;
}
