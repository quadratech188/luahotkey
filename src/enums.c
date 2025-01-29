#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include "libhotkey.h"
#include "libhotkey-action.h"

enum libhotkey_state state_get(lua_State* L, int index) {
	const char* state = luaL_checkstring(L, index);

	if (strcmp("Up", state) == 0)
		return LIBHOTKEY_STATE_UP;
	else
		return LIBHOTKEY_STATE_DOWN;
}

enum libhotkey_transition transition_get(lua_State* L, int index) {
	const char* transition = luaL_checkstring(L, index);

	if (strcmp("Press", transition) == 0)
		return LIBHOTKEY_TRANSITION_PRESS;
	else if (strcmp("Autorepeat", transition) == 0)
		return LIBHOTKEY_TRANSITION_AUTOREPEAT;
	else
		return LIBHOTKEY_TRANSITION_RELEASE;
}

enum libhotkey_action_type action_type_get(lua_State* L, int index) {
	const char* action_type = luaL_checkstring(L, index);

	if (strcmp("Press", action_type) == 0)
		return LIBHOTKEY_ACTION_PRESS;
	else if (strcmp("Autorepeat", action_type) == 0)
		return LIBHOTKEY_ACTION_AUTOREPEAT;
	else if (strcmp("Release", action_type) == 0)
		return LIBHOTKEY_ACTION_RELEASE;
	else if (strcmp("Mirror", action_type) == 0)
		return LIBHOTKEY_ACTION_MIRROR;
	else if (strcmp("Require_up", action_type) == 0)
		return LIBHOTKEY_ACTION_REQUIRE_UP;
	else if (strcmp("Require_down", action_type) == 0)
		return LIBHOTKEY_ACTION_REQUIRE_DOWN;
	else
		return LIBHOTKEY_ACTION_CUSTOM;
}
