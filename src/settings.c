#include "settings.h"

#include <lauxlib.h>

bool should_grab = true;

int settings_grab_l(lua_State* L);

static const luaL_Reg functions[] = {
	{"grab", settings_grab_l},
	{NULL, NULL}
};

void settings_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "settings");
}

int settings_grab_l(lua_State* L) {
	should_grab = lua_toboolean(L, 1);
	return 0;
}

bool settings_grab() {
	return should_grab;
}
