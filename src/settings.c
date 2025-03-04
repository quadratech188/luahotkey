#include "settings.h"

#include <lauxlib.h>

static bool should_grab = true;
static const char* input;
static const char* output;
static const char* socket;
static bool use_socket = false;
int socket_handler = LUA_NOREF;

int settings_grab_l(lua_State* L);
int settings_input_l(lua_State* L);
int settings_output_l(lua_State* L);
int settings_socket_l(lua_State* L);
int settings_socket_handler_l(lua_State* L);
int settings_use_socket_l(lua_State* L);

static const luaL_Reg functions[] = {
	{"grab", settings_grab_l},
	{"input", settings_input_l},
	{"output", settings_output_l},
	{"socket", settings_socket_l},
	{"socket_handler", settings_socket_handler_l},
	{"use_socket", settings_use_socket_l},
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

int settings_socket_l(lua_State* L) {
	socket = luaL_checkstring(L, 1);
	return 0;
}

int settings_socket_handler_l(lua_State* L) {
	socket_handler = luaL_ref(L, LUA_REGISTRYINDEX);
	return 0;
}

int settings_use_socket_l(lua_State* L) {
	use_socket = lua_toboolean(L, 1);
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

const char* settings_socket() {
	return socket;
}

void settings_push_socket_handler(lua_State* L) {
	lua_rawgeti(L, LUA_REGISTRYINDEX, socket_handler);
}

bool settings_use_socket() {
	return use_socket;
}
