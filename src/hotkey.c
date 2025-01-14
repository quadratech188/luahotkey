#include "hotkey.h"

#include <lua.h>
#include <lauxlib.h>

#include "../libhotkey/src/hotkey.h"

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

static void handler(struct libhotkey_hotkey*, struct libhotkey_update);

void hotkey_open(lua_State* L) {
	libhotkey_hotkey_set_handler(handler);

	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "hotkey");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_hotkey* hotkey_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int hotkey_new(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_getfield(L, 1, "updates");

	struct libhotkey_hotkey* hotkey;

	if (lua_istable(L, -1)) {
		int updates_length = lua_rawlen(L, -1);

		hotkey = lua_newuserdata(L, sizeof(struct libhotkey_hotkey)
				+ updates_length * sizeof(struct libhotkey_update));

		hotkey->updates_length = updates_length;

		lua_getfield(L, 1, "updates"); // lua_newuserdata means that the array is no longer on
										  // top of the stack, get it again

		for (int i = 0; i < updates_length; i++) {
			lua_geti(L, -1, i + 1);
			hotkey->updates[i] = *update_get(L, -1);
			lua_pop(L, 1);
		}
		hotkey->type = LIBHOTKEY_HOTKEY_KEYSTROKES;
	}
	else {
		hotkey = lua_newuserdata(L, sizeof(struct libhotkey_hotkey));
		hotkey->updates_length = 0;
		hotkey->type = 0;
	}

	lua_pop(L, 1);

	lua_getfield(L, 1, "criteria");
	if (!lua_isnil(L, -1))
		hotkey->criteria = criteria_get(L, -1);
	else
	 	hotkey->criteria = NULL;

	lua_pop(L, 1);

	luaL_setmetatable(L, metatable_name);

	return 1;

	// TODO: Add support for lua handlers
}

static void handler(struct libhotkey_hotkey* hotkey, struct libhotkey_update update) {
	// TODO
}
