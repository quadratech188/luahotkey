#include <lua.h>

#include "../libhotkey/src/key.h"

void keystate_open(lua_State* L);
struct libhotkey_keystate* keystate_get(lua_State* L, int index);
