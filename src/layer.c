#include "layer.h"

#include <stddef.h>

#include <lauxlib.h>
#include "libhotkey-layer.h"

#include "hotkey.h"
#include "node_ref.h"

static const char* metatable_name = "lhk.Layer";

int layer_new(lua_State* L);
int layer_set_next(lua_State* L);
int layer_register(lua_State* L);
int layer_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", layer_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"set_next", layer_set_next},
	{"register", layer_register},
	{"__gc", layer_gc},
	{NULL, NULL}
};

const char* layer_metatablename() {
	return metatable_name;
}

void layer_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "layer"); // lhk.layer = <table>

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1); // duplicate the metatable
	lua_setfield(L, -2, "__index"); // mt.__index = mt
	luaL_register(L, NULL, methods);
	lua_pop(L, 1); // pop metatable
}

struct libhotkey_layer* layer_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int layer_new(lua_State* L) {
	libhotkey_layer_init(lua_newuserdata(L, libhotkey_layer_size()));

	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}

int layer_gc(lua_State* L) {
	libhotkey_layer_cleanup(layer_get(L, 1));
	return 0;
}

int layer_set_next(lua_State* L) {
	libhotkey_layer_set_next(layer_get(L, 1), node_ref_get(L, 2));
	return 0;
}

int layer_register(lua_State* L) {
	libhotkey_register_hotkey(layer_get(L, 1), luaL_checkinteger(L, 2), hotkey_get(L, 3));
	return 0;
}
