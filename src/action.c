#include <lua.h>
#include <lauxlib.h>
#include "../libhotkey/src/action.h"

#include "enums.h"

static const char* metatable_name = "lhk.Action";

int action_new(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", action_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{NULL, NULL}
};

void action_open(lua_State* L) {
	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "action");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_action* action_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int action_new(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = action_type_get(L, 2);

	if (action->type == LIBHOTKEY_ACTION_CUSTOM) {
		// TODO
	}
	else {
		action->keycode = luaL_checkinteger(L, 1);
	}

	luaL_setmetatable(L, metatable_name);

	return 1;
}
