#include "settings.h"

#include <lauxlib.h>

bool settings_should_grab = true;

int settings_grab(lua_State* L);

static const luaL_Reg functions[] = {
	{"grab", settings_grab},
	{NULL, NULL}
};

void settings_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "settings");
}

int settings_grab(lua_State* L) {
	settings_should_grab = lua_toboolean(L, 1);
	return 0;
}
