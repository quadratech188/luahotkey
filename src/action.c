#include <lua.h>
#include <lauxlib.h>
#include "libhotkey-action.h"

#include "update.h"
#include "enums.h"
#include "main.h"

static const char* metatable_name = "lhk.Action";


int action_new(lua_State* L);
int action_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"new", action_new},
	{NULL, NULL}
};

static const luaL_Reg methods[] = {
	{"__gc", action_gc},
	{NULL, NULL}
};

static void action_handler(struct libhotkey_action* action, struct libhotkey_update update);

void action_open(lua_State* L) {
	libhotkey_set_action_handler(action_handler);

	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);
	lua_setfield(L, -2, "action");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

struct libhotkey_action* action_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int action_new(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = action_type_get(L, 2);

	if (action->type == LIBHOTKEY_ACTION_CUSTOM) {
		luaL_checktype(L, 1, LUA_TFUNCTION);
		lua_pushvalue(L, 1);

		action->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX); // Putting an integer into a ptr field, shitty but better than mallocing
	}
	else {
		action->keycode = luaL_checkinteger(L, 1);
	}

	luaL_setmetatable(L, metatable_name);

	return 1;
}

int action_gc(lua_State* L) {
	struct libhotkey_action* action = action_get(L, 1);

	if (action->type == LIBHOTKEY_ACTION_CUSTOM)
		luaL_unref(L, LUA_REGISTRYINDEX, (intptr_t)action->extra_data);
	
	return 0;
}

static void action_handler(struct libhotkey_action* action, struct libhotkey_update update) {
	lua_geti(lhk_L, LUA_REGISTRYINDEX, (intptr_t)action->extra_data);
	update_push(lhk_L, update);

	int err = lua_pcall(lhk_L, 1, 0, 0);

	// TODO: proper error handling
	if (err != 0) {
		fprintf(stderr, lua_tostring(lhk_L, err));
	}
}
