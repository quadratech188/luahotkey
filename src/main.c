#include "main.h"

#include <errno.h>
#include <lauxlib.h>
#include <string.h>

#include "action.h"
#include "criteria.h"
#include "hotkey.h"
#include "io.h"
#include "keynode.h"
#include "keystate.h"
#include "layer.h"
#include "node_ref.h"
#include "settings.h"
#include "socket.h"
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
	luaL_register(L, NULL, functions);

	action_open(L);
	criteria_open(L);
	hotkey_open(L);
	keynode_open(L);
	keystate_open(L);
	layer_open(L);
	settings_open(L);
	update_open(L);

	return 1;
}

static struct libhotkey_node_ref root;
int root_ref = LUA_NOREF;
static bool stop;

int lhk_start(lua_State* L) {
	int error = io_init();

	switch(error) {
		case 0: break;
		case LIBHOTKEY_OPEN_INPUT_FAIL:
			return luaL_error(L, "Failed to open input %s: %s", settings_input(), strerror(errno));
		case LIBHOTKEY_GRAB_INPUT_FAIL:
			return luaL_error(L, "Failed to grab input %s: %s", settings_input(), strerror(errno));
		case LIBHOTKEY_CREATE_OUTPUT_FAIL:
			return luaL_error(L, "Failed to create output %s: %s", settings_output(), strerror(errno));
	}

	libhotkey_set_output(io_queue_update);
	stop = false;

	if (settings_use_socket()) {
		error = socket_init();
		if (error < 0) return luaL_error(L, "Failed to open socket %s: %s", settings_socket(), strerror(errno));

		while (io_await_update()) {
			if (socket_push(L)) {
				settings_push_socket_handler(L);
				lua_pushvalue(L, -2); // push the string
				error = lua_pcall(L, 1, 0, 0);
				if (error != 0)
					fprintf(stderr, "%s\n", lua_tostring(L, -1));
			}

			libhotkey_send(root, io_get_update());
			if (stop) break;
			io_sync_updates();
		}
	}
	else {
		while (io_await_update()) {
			libhotkey_send(root, io_get_update());
			if (stop) break;
			io_sync_updates();
		}
	}

	io_cleanup();
	socket_close();

	return 0;
}

int lhk_stop(lua_State* L) {
	stop = true;
	return 0;
}

int lhk_set_root(lua_State* L) {
	root = node_ref_get(L, 1);

	luaL_unref(L, LUA_REGISTRYINDEX, root_ref); // Also works when root_ref is LUA_NOREF

	lua_pushvalue(L, 1);
	root_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	
	return 0;
}
