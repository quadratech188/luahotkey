#include <lua.h>

void hotkey_open(lua_State* L);
struct libhotkey_hotkey* hotkey_get(lua_State* L, int index);
