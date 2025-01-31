#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include "libhotkey.h"

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
