#include "layer.h"

#include <stddef.h>

#include <lauxlib.h>
#include "../libhotkey/src/loop.h"
#include "libhotkey-layer.h"

#include "hotkey.h"

static const char* metatable_name = "lhk.Layer";

int layer_new(lua_State* L);
int layer_set_next_layer(lua_State* L);
int layer_register(lua_State* L);
int layer_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", layer_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"set_next_layer", layer_set_next_layer},
	{"register", layer_register},
	{"__gc", layer_gc},
	{NULL, NULL}
};

void layer_open(lua_State* L) {
	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "layer"); // lhk.layer = <table>

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1); // duplicate the metatable
	lua_setfield(L, -2, "__index"); // mt.__index = mt
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1); // pop metatable
}

struct libhotkey_layer* layer_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int layer_new(lua_State* L) {
	libhotkey_layer_init(lua_newuserdata(L, libhotkey_layer_size()));

	luaL_setmetatable(L, metatable_name);

	return 1;
}

int layer_gc(lua_State* L) {
	libhotkey_layer_cleanup(layer_get(L, 1));
	return 0;
}

int layer_set_next_layer(lua_State* L) {
	if (lua_isnil(L, 2)) {
		libhotkey_layer_set_next(layer_get(L, 1), libhotkey_null_ref());
		return 0;
	}

	libhotkey_layer_set_next(layer_get(L, 1), libhotkey_layer_ref(layer_get(L, 2)));

	return 0;
}

int layer_register(lua_State* L) {
	libhotkey_register_hotkey(layer_get(L, 1), luaL_checkinteger(L, 2), hotkey_get(L, 3));
	return 0;
}
