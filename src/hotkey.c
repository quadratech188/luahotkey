#include "hotkey.h"

#include <stdint.h>

#include <lua.h>
#include <lauxlib.h>

#include "libhotkey-action.h"
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
	lua_pop(L, 1);

	struct libhotkey_hotkey* hotkey = lua_newuserdata(L, sizeof(struct libhotkey_hotkey)
			+ actions_length * sizeof(struct libhotkey_action));
	// {} hotkey

	hotkey->actions_length = actions_length;

	lua_newtable(L); // fenv
	// {} hotkey fenv

	lua_getfield(L, 1, "actions"); // lua_newuserdata means that the array is no longer on
								   // top of the stack, get it again
	// {} hotkey fenv actions

	for (int i = 0; i < actions_length; i++) {
		lua_rawgeti(L, -1, i + 1);
		hotkey->actions[i] = *action_get(L, -1);

		// Store a reference to custom functions in fenv so that they're not garbage collected
		if (hotkey->actions[i].type == LIBHOTKEY_ACTION_CUSTOM)
			lua_rawseti(L, -3, lua_objlen(L, -3) + 1);
		else
			lua_pop(L, 1);
	}
	lua_pop(L, 1);
	// {} hotkey fenv
	
	lua_setfenv(L, -2);
	// {} hotkey

	lua_getfield(L, 1, "criteria");
	if (!lua_isnil(L, -1)) {
		hotkey->criteria = criteria_new_or_get(L, -1);
		lua_pop(L, 1);

		// Store a reference to the criteria in fenv
		lua_getfenv(L, -1);
		lua_pushstring(L, "criteria");
		lua_getfield(L, 1, "criteria");
		lua_settable(L, -3);
		lua_pop(L, 1); // fenv
	}
	else {
	 	hotkey->criteria = NULL;
		lua_pop(L, 1);
	}
	// {} hotkey

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
