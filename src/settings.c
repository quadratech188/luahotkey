#include "settings.h"

#include <lauxlib.h>

bool should_grab = true;
const char* input;
const char* output;

int settings_grab_l(lua_State* L);
int settings_input_l(lua_State* L);
int settings_output_l(lua_State* L);

static const luaL_Reg functions[] = {
	{"grab", settings_grab_l},
	{"input", settings_input_l},
	{"output", settings_output_l},
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

int settings_input_l(lua_State* L) {
	input = luaL_checkstring(L, 1);
	return 0;
}

int settings_output_l(lua_State* L) {
	output = luaL_checkstring(L, 1);
	return 0;
}

bool settings_grab() {
	return should_grab;
}

const char* settings_input() {
	return input;
}

const char* settings_output() {
	return output;
}
