#include <lua.h>
#include <lauxlib.h>

#include "libhotkey-keynode.h"
#include "libhotkey-layer.h"
#include "libhotkey.h"

#include "keynode.h"
#include "layer.h"

struct libhotkey_node_ref node_ref_get(lua_State* L, int index) {
	if (lua_isnoneornil(L, index))
		return libhotkey_null_ref();

	// https://github.com/lunarmodules/lua-compat-5.3/blob/master/c-api/compat-5.3.c#L285C14-L285C18
	
	void* p = lua_touserdata(L, index);
	
	lua_getmetatable(L, index);
	
	luaL_getmetatable(L, layer_metatablename());
	if (lua_rawequal(L, -1, -2)) {
		lua_pop(L, 2);
		return libhotkey_layer_ref(p);
	}
	lua_pop(L, 1); // layer metatable

	luaL_getmetatable(L, keynode_metatablename());
	if (lua_rawequal(L, -1, -2)) {
		lua_pop(L, 2);
		return libhotkey_keynode_ref(p);
	}

	luaL_typerror(L, index, "lhk.Keynode|lhk.Layer|nil");

	__builtin_unreachable();
}
