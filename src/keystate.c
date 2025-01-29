#include "keystate.h"

#include <string.h>
#include <stddef.h>

#include <lauxlib.h>

#include "enums.h"

static const char* metatable_name = "lhk.Keystate";

int keystate_new(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", keystate_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{NULL, NULL}
};

void keystate_open(lua_State* L) {
	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "keystate");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_keystate* keystate_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int keystate_new(lua_State* L) {
	struct libhotkey_keystate* keystate = lua_newuserdata(L, sizeof(struct libhotkey_keystate));

	keystate->keycode = luaL_checkinteger(L, 1);
	keystate->state = state_get(L, 2);

	luaL_setmetatable(L, metatable_name);

	return 1;
}
