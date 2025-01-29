#include <lua.h>
#include <lauxlib.h>

#include "libhotkey.h"
#include "libhotkey-layer.h"

#include "layer.h"

struct libhotkey_node_ref node_ref_get(lua_State* L, int index) {
	if (lua_isnoneornil(L, index))
		return libhotkey_null_ref();

	struct libhotkey_layer* layer = layer_test(L, index);

	if (layer != NULL) return libhotkey_layer_ref(layer);

	luaL_typeerror(L, index, "lhk.Layer or nil");

	__builtin_unreachable();
}
