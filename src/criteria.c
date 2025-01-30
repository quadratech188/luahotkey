#include "criteria.h"

#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include "libhotkey-criteria.h"

#include "enums.h"
#include "keynode.h"
#include "keystate.h"
#include "main.h"
#include "update.h"

static const char* metatable_name = "lhk.Criteria";

int criteria_new(lua_State* L);
int criteria_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", criteria_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"__gc", criteria_gc},
	{NULL, NULL}
};

static bool handler(struct libhotkey_criteria*, struct libhotkey_update);

void criteria_open(lua_State* L) {
	libhotkey_set_criteria_handler(handler);

	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "criteria");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_criteria* criteria_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int criteria_new(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "keynode");

	struct libhotkey_criteria* criteria;

	if (!lua_isnil(L, -1)) {
		lua_getfield(L, 1, "keystates");

		int keystates_length = luaL_len(L, -1);

		lua_pop(L, 1); // keynode
		lua_pop(L, 1); // keystates

		criteria = lua_newuserdata(L, sizeof(struct libhotkey_criteria)
				+ keystates_length * sizeof(struct libhotkey_keystate));

		criteria->keystates_length = keystates_length;

		lua_getfield(L, 1, "keynode");
		criteria->keynode = keynode_get(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, 1, "keystates");

		for (int i = 0; i < keystates_length; i++) {
			lua_geti(L, -1, i + 1);
			criteria->keystates[i] = *keystate_get(L, -1);
			lua_pop(L, 1);
		}
		criteria->type = LIBHOTKEY_CRITERIA_KEYSTATE;

		lua_pop(L, 1);
	}
	else {
		criteria = lua_newuserdata(L, sizeof(struct libhotkey_criteria));
		criteria->keystates_length = 0;
		criteria->type = 0;
	}

	lua_getfield(L, 1, "transition");
	if (!lua_isnil(L, -1)) {
		criteria->type |= LIBHOTKEY_CRITERIA_TRANSITION;

		criteria->transition = transition_get(L, -1);
	}

	lua_pop(L, 1);

	lua_getfield(L, 1, "handler");
	if (!lua_isnil(L, -1)) {
		criteria->type |= LIBHOTKEY_CRITERIA_HANDLER;
		luaL_checktype(L, -1, LUA_TFUNCTION);
		criteria->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX);
		// luaL_ref pops for us
	}
	else {
		lua_pop(L, 1);
	}

	luaL_setmetatable(L, metatable_name);

	return 1;
}

int criteria_gc(lua_State* L) {
	struct libhotkey_criteria* criteria = criteria_get(L, 1);

	if (criteria->type & LIBHOTKEY_CRITERIA_HANDLER)
		luaL_unref(L, LUA_REGISTRYINDEX, (intptr_t)criteria->extra_data);

	return 0;
}

static bool handler(struct libhotkey_criteria* criteria, struct libhotkey_update update) {
	lua_geti(lhk_L, LUA_REGISTRYINDEX, (intptr_t)criteria->extra_data);
	update_push(lhk_L, update);

	int err = lua_pcall(lhk_L, 1, 1, 0);

	if (err != 0) {
		fprintf(stderr, lua_tostring(lhk_L, err));
	}

	bool result = lua_toboolean(lhk_L, -1);
	lua_pop(lhk_L, 1);

	return result;
}
