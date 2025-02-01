#include "hotkey.h"

#include <lua.h>
#include <lauxlib.h>

#include "libhotkey-hotkey.h"

#include "action.h"
#include "criteria.h"
#include "update.h"

static const char* metatable_name = "lhk.Hotkey";

int hotkey_new(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", hotkey_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{NULL, NULL}
};

void hotkey_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "hotkey");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, functions);
	lua_pop(L, 1);
}

struct libhotkey_hotkey* hotkey_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int hotkey_new(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_getfield(L, 1, "actions");

	int actions_length = lua_objlen(L, -1);

	struct libhotkey_hotkey* hotkey = lua_newuserdata(L, sizeof(struct libhotkey_hotkey)
			+ actions_length * sizeof(struct libhotkey_action));

	hotkey->actions_length = actions_length;

	lua_getfield(L, 1, "actions"); // lua_newuserdata means that the array is no longer on
								   // top of the stack, get it again

	for (int i = 0; i < actions_length; i++) {
		lua_rawgeti(L, -1, i + 1);
		hotkey->actions[i] = *action_get(L, -1);
		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	lua_getfield(L, 1, "criteria");
	if (!lua_isnil(L, -1))
		hotkey->criteria = criteria_get(L, -1);
	else
	 	hotkey->criteria = NULL;
	lua_pop(L, 1);

	lua_getfield(L, 1, "passthrough");
	if (lua_toboolean(L, -1))
		hotkey->flags = LIBHOTKEY_HOTKEY_PASSTHROUGH;
	else
	 	hotkey->flags = 0;
	lua_pop(L, 1);

	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);

	return 1;
}
