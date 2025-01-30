#include "main.h"

#include <errno.h>
#include <lauxlib.h>
#include <string.h>

#include "../libhotkey/src/loop.h"
#include "../libhotkey/src/io.h"
#include "libhotkey-layer.h"

#include "action.h"
#include "criteria.h"
#include "hotkey.h"
#include "keynode.h"
#include "keystate.h"
#include "layer.h"
#include "node_ref.h"
#include "update.h"

lua_State* lhk_L;

int lhk_start(lua_State* L);
int lhk_stop(lua_State* L);
int lhk_set_root(lua_State* L);

static const luaL_Reg functions[] = {
	{"start", lhk_start},
	{"stop", lhk_stop},
	{"set_root", lhk_set_root},
	{NULL, NULL}
};

int luaopen_lhk_core(lua_State* L) {
	lhk_L = L;

	lua_newtable(L);
	luaL_setfuncs(L, functions, 0);

	action_open(L);
	criteria_open(L);
	hotkey_open(L);
	keynode_open(L);
	keystate_open(L);
	layer_open(L);
	update_open(L);

	return 1;
}

int lhk_start(lua_State* L) {
	int error = libhotkey_io_init(luaL_checkstring(L, 1), luaL_checkstring(L, 2));

	switch(error) {
		case 0: break;
		case LIBHOTKEY_OPEN_INPUT_FAIL:
			return luaL_error(L, "Failed to open input %s: %s", luaL_checkstring(L, 1), strerror(errno));
		case LIBHOTKEY_GRAB_INPUT_FAIL:
			return luaL_error(L, "Failed to grab input %s: %s", luaL_checkstring(L, 1), strerror(errno));
		case LIBHOTKEY_CREATE_OUTPUT_FAIL:
			return luaL_error(L, "Failed to create output %s: %s", luaL_checkstring(L, 2), strerror(errno));
	}

	libhotkey_loop_start();

	return 0;
}

int lhk_stop(lua_State* L) {
	libhotkey_loop_stop();
	libhotkey_io_cleanup();
	return 0;
}

int lhk_set_root(lua_State* L) {
	libhotkey_loop_set_root(node_ref_get(L, 1));
	return 0;
}
