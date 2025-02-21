#include <stdint.h>

#include <lua.h>
#include <lauxlib.h>
#include "libhotkey-action.h"

#include "enums.h"
#include "keynode.h"
#include "main.h"
#include "update.h"

static const char* metatable_name = "lhk.Action";


int action_press(lua_State* L);
int action_release(lua_State* L);
int action_autorepeat(lua_State* L);
int action_mirror(lua_State* L);
int action_require_up(lua_State* L);
int action_require_down(lua_State* L);
int action_enforce(lua_State* L);
int action_enforce_from_down(lua_State* L);
int action_enforce_from_up(lua_State* L);
int action_custom(lua_State* L);

int action_gc(lua_State* L);

static const luaL_Reg functions[] = {
	{"press", action_press},
	{"release", action_release},
	{"autorepeat", action_autorepeat},
	{"mirror", action_mirror},
	{"require_up", action_require_up},
	{"require_down", action_require_down},
	{"enforce", action_enforce},
	{"enforce_from_down", action_enforce_from_down},
	{"enforce_from_up", action_enforce_from_up},
	{"custom", action_custom},
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
	luaL_register(L, NULL, functions);
	lua_setfield(L, -2, "action");

	luaL_newmetatable(L, metatable_name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, methods);
	lua_pop(L, 1);
}

struct libhotkey_action* action_get(lua_State* L, int index) {
	return luaL_checkudata(L, index, metatable_name);
}

int action_press(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_PRESS;
	action->keycode = luaL_checkinteger(L, 1);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_release(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_RELEASE;
	action->keycode = luaL_checkinteger(L, 1);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_autorepeat(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_AUTOREPEAT;
	action->keycode = luaL_checkinteger(L, 1);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_mirror(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_MIRROR;
	action->keycode = luaL_checkinteger(L, 1);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}

int action_require_up(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_REQUIRE_UP;
	action->require.keynode = keynode_get(L, 1);
	action->require.keycode = luaL_checkinteger(L, 2);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_require_down(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_REQUIRE_DOWN;
	action->require.keynode = keynode_get(L, 1);
	action->require.keycode = luaL_checkinteger(L, 2);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_enforce(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_ENFORCE;
	action->enforce.reference = keynode_get(L, 1);
	action->enforce.keycode = luaL_checkinteger(L, 2);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_enforce_from_down(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_ENFORCE_FROM_DOWN;
	action->enforce.reference = keynode_get(L, 1);
	action->enforce.keycode = luaL_checkinteger(L, 2);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_enforce_from_up(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	action->type = LIBHOTKEY_ACTION_ENFORCE_FROM_UP;
	action->enforce.reference = keynode_get(L, 1);
	action->enforce.keycode = luaL_checkinteger(L, 2);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}
int action_custom(lua_State* L) {
	struct libhotkey_action* action = lua_newuserdata(L, sizeof(struct libhotkey_action));
	luaL_checktype(L, 1, LUA_TFUNCTION);
	action->type = LIBHOTKEY_ACTION_CUSTOM;
	lua_pushvalue(L, 1);
	action->extra_data = (void*)(intptr_t)luaL_ref(L, LUA_REGISTRYINDEX);
	luaL_getmetatable(L, metatable_name);
	lua_setmetatable(L, -2);
	return 1;
}

int action_gc(lua_State* L) {
	struct libhotkey_action* action = action_get(L, 1);

	if (action->type == LIBHOTKEY_ACTION_CUSTOM)
		luaL_unref(L, LUA_REGISTRYINDEX, (intptr_t)action->extra_data);
	
	return 0;
}

static void action_handler(struct libhotkey_action* action, struct libhotkey_update update) {
	lua_rawgeti(lhk_L, LUA_REGISTRYINDEX, (intptr_t)action->extra_data);
	update_push(lhk_L, update);

	int err = lua_pcall(lhk_L, 1, 0, 0);

	// TODO: proper error handling
	if (err != 0) {
		fprintf(stderr, "%s\n", lua_tostring(lhk_L, -1));
	}
}
