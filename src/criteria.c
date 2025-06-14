#include "criteria.h"

#include <string.h>
#include <stdint.h>

#include <lauxlib.h>
#include <lua.h>
#include "libhotkey-criteria.h"

#include "enums.h"
#include "keynode.h"
#include "keystate.h"
#include "main.h"
#include "update.h"

enum incides {
	KEYNODE
};

static const char* metatable_name = "lhk.Criteria";

int criteria_new(lua_State* L);
int criteria_add(lua_State* L);
int criteria_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", criteria_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"__gc", criteria_gc},
	{"__add", criteria_add},
	{NULL, NULL}
};

static bool handler(struct libhotkey_criteria*, struct libhotkey_update);

void criteria_open(lua_State* L) {
	libhotkey_set_criteria_handler(handler);

	lua_newtable(L);
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "criteria");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, methods);
	lua_pop(L, 1);
}

struct libhotkey_criteria* criteria_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int criteria_new(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);

	lua_getfield(L, 1, "keystates"); // T | T.keystates

	bool uses_keystate = false;
	size_t length = 0;

	if (!lua_isnil(L, -1)) {
		uses_keystate = true;
		length = lua_objlen(L, -1);
	}

	lua_pop(L, 1); // T
	
	struct libhotkey_criteria* criteria = lua_newuserdata(L, sizeof(struct libhotkey_criteria)
			+ length * sizeof(struct libhotkey_keystate)); // T | criteria
	criteria->type = 0;

	// fenv
	lua_newtable(L); // T | criteria | {}
	lua_setfenv(L, -2); // T | criteria

	if (uses_keystate) {
		criteria->type |= LIBHOTKEY_CRITERIA_KEYSTATE;
		criteria->keystates_length = length;

		lua_getfield(L, 1, "keynode"); // T | criteria | T.keynode
		if (lua_isnil(L, -1))
			return luaL_argerror(L, 1, "lhk.Criteria with keystates also require a keynode");
		
		criteria->keynode = keynode_get(L, -1);

		// Add reference to keynode in fenv
		lua_getfenv(L, -2); // T | criteria | T.keynode | criteria.fenv
		
		lua_pushnumber(L, KEYNODE); // T | criteria | T.keynode | criteria.fenv | KEYNODE
		lua_pushvalue(L, -3); // T | criteria | T.keynode | criteria.fenv | KEYNODE | keynode
		lua_settable(L, -3); // T | criteria | T.keynode | criteria.fenv
		
		lua_pop(L, 2); // T | criteria
		
		lua_getfield(L, 1, "keystates"); // T | criteria | T.keystates

		for (size_t i = 0; i < length; i++) {
			lua_rawgeti(L, -1, i + 1); // T | criteria | T.keystates | T.keystates[i]
			criteria->keystates[i] = *keystate_get(L, -1);
			lua_pop(L, 1); // T | criteria | T.keystates
		}
		lua_pop(L, 1); // T | criteria
	}
	else {
		criteria->keystates_length = 0;
	}

	lua_getfield(L, 1, "transition"); // T | criteria | T.transition
	if (!lua_isnil(L, -1)) {
		criteria->type |= LIBHOTKEY_CRITERIA_TRANSITION;
		criteria->transition = transition_get(L, -1);
	}

	lua_pop(L, 1); // T | criteria

	lua_getfield(L, 1, "handler"); // T | criteria | T.handler
	if (!lua_isnil(L, -1)) {
		criteria->type |= LIBHOTKEY_CRITERIA_HANDLER;
		luaL_checktype(L, -1, LUA_TFUNCTION);

		criteria->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX); // T | criteria
		// luaL_ref pops for us
	}
	else
		lua_pop(L, 1); // T | criteria

	luaL_getmetatable(L, metatable_name); // T | criteria | metatable
	lua_setmetatable(L, -2); // T | criteria

	return 1;
}

int criteria_add(lua_State* L) {
	struct libhotkey_criteria* lhs = criteria_get(L, 1);
	struct libhotkey_criteria* rhs = criteria_get(L, 2);

	struct libhotkey_criteria* result = lua_newuserdata(L, sizeof(struct libhotkey_criteria)
			+ (lhs->keystates_length + rhs->keystates_length) * sizeof(struct libhotkey_keystate)); // lhs | rhs | result
	result->type = lhs->type | rhs->type;
	
	result->keystates_length = lhs->keystates_length + rhs->keystates_length;
	memcpy(result->keystates, lhs->keystates,
			lhs->keystates_length * sizeof(struct libhotkey_keystate));
	memcpy(result->keystates + lhs->keystates_length, rhs->keystates,
			rhs->keystates_length * sizeof(struct libhotkey_keystate));

	if (lhs->type & LIBHOTKEY_CRITERIA_KEYSTATE) {
		lua_getfenv(L, 1); // lhs | rhs | result | lhs.fenv
		lua_setfenv(L, -2); // lhs | rhs | result
		result->keynode = lhs->keynode;
	}
	else if (rhs->type & LIBHOTKEY_CRITERIA_KEYSTATE) {
		lua_getfenv(L, 2); // lhs | rhs | result | rhs.fenv
		lua_setfenv(L, -2); // lhs | rhs | result
		result->keynode = rhs->keynode;
	}

	if (lhs->type & LIBHOTKEY_CRITERIA_TRANSITION)
		result->transition = lhs->transition;
	else if (rhs->type & LIBHOTKEY_CRITERIA_TRANSITION)
	 	result->transition = rhs->transition;

	if (lhs->type & LIBHOTKEY_CRITERIA_HANDLER) {
		// New ref; the old one might get garbage collected
		lua_rawgeti(L, LUA_REGISTRYINDEX, (intptr_t)lhs->extra_data); // lhs | rhs | result | lhs.extra_data
		result->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX); // lhs | rhs | result
	}
	else if (rhs->type & LIBHOTKEY_CRITERIA_HANDLER) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, (intptr_t)rhs->extra_data); // lhs | rhs | result | rhs.extra_data
		result->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX); // lhs | rhs | result
	}

	luaL_getmetatable(L, metatable_name); // T | result | metatable
	lua_setmetatable(L, -2); // T | result

	return 1;
}

int criteria_gc(lua_State* L) {
	struct libhotkey_criteria* criteria = criteria_get(L, 1);

	if (criteria->type & LIBHOTKEY_CRITERIA_HANDLER)
		luaL_unref(L, LUA_REGISTRYINDEX, (intptr_t)criteria->extra_data);

	return 0;
}

static bool handler(struct libhotkey_criteria* criteria, struct libhotkey_update update) {
	lua_rawgeti(lhk_L, LUA_REGISTRYINDEX, (intptr_t)criteria->extra_data);
	update_push(lhk_L, update);

	int err = lua_pcall(lhk_L, 1, 1, 0);

	if (err != 0) {
		fprintf(stderr, lua_tostring(lhk_L, err));
	}

	bool result = lua_toboolean(lhk_L, -1);
	lua_pop(lhk_L, 1);

	return result;
}
