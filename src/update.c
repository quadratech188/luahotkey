#include "update.h"

#include <string.h>
#include <stddef.h>

#include <lauxlib.h>

#include "enums.h"
#include "libhotkey.h"

static const char* metatable_name = "lhk.Update";

int update_new(lua_State* L);
int update_index(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", update_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"__index", update_index},
	{NULL, NULL}
};

void update_open(lua_State* L) {
	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "update");

	luaL_newmetatable(L, metatable_name);
	luaL_register(L, NULL, methods);
	lua_pop(L, 1);
}

struct libhotkey_update* update_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

void update_push(lua_State* L, struct libhotkey_update update) {
	*(struct libhotkey_update*)lua_newuserdata(L, sizeof(struct libhotkey_update)) = update;
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
}

int update_new(lua_State* L) {
	struct libhotkey_update* update = lua_newuserdata(L, sizeof(struct libhotkey_update));

	update->keycode = luaL_checkinteger(L, 1);
	update->transition = transition_get(L, 2);

	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);

	return 1;
}

int update_index(lua_State* L) {
	const char* index = luaL_checkstring(L, 2);
	if (strcmp(index, "keycode") == 0) {
		lua_pushinteger(L, update_get(L, 1)->keycode);
		return 1;
	}
	if (strcmp(index, "transition") == 0) {
		switch(update_get(L, 1)->transition) {
			case LIBHOTKEY_TRANSITION_PRESS:
				lua_pushstring(L, "Press"); break;
			case LIBHOTKEY_TRANSITION_RELEASE:
				lua_pushstring(L, "Release"); break;
			case LIBHOTKEY_TRANSITION_AUTOREPEAT:
				lua_pushstring(L, "Autorepeat");
		}
		return 1;
	}
	return 0;
}
