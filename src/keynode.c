#include "keynode.h"

#include <lauxlib.h>

#include "node_ref.h"

#include "libhotkey-keynode.h"

enum indices {
	NEXT
};

static const char* metatable_name = "lhk.Keynode";

int keynode_new(lua_State* L);
int keynode_state(lua_State* L);
int keynode_set_next(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", keynode_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"state", keynode_state},
	{"set_next", keynode_set_next},
	{NULL, NULL}
};

const char* keynode_metatablename() {
	return metatable_name;
}

void keynode_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "keynode");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, methods);
	lua_pop(L, 1);
}

struct libhotkey_keynode* keynode_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int keynode_new(lua_State* L) {
	libhotkey_keynode_init(lua_newuserdata(L, libhotkey_keynode_size()));

	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);

	lua_newtable(L);
	lua_setfenv(L, -2);

	return 1;
}

int keynode_set_next(lua_State* L) {
	libhotkey_keynode_set_next(keynode_get(L, 1), node_ref_get(L, 2));

	lua_getfenv(L, 1);
	lua_pushnumber(L, NEXT);
	lua_pushvalue(L, 2);
	lua_settable(L, -3); // fenv[1] = next

	return 0;
}

int keynode_state(lua_State* L) {
	if (libhotkey_keynode_state(keynode_get(L, 1), luaL_checkinteger(L, 2)) == LIBHOTKEY_STATE_DOWN)
		lua_pushstring(L, "Down");
	else
	 	lua_pushstring(L, "Up");

	return 1;
}
