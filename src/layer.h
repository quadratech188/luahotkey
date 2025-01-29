#include <lua.h>

void layer_open(lua_State* L);

struct libhotkey_layer* layer_get(lua_State* L, int index);
struct libhotkey_layer* layer_test(lua_State* L, int index);
