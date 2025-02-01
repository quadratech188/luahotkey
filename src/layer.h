#include <lua.h>

const char* layer_metatablename();

void layer_open(lua_State* L);

struct libhotkey_layer* layer_get(lua_State* L, int index);
