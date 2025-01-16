#include <lua.h>
#include "../libhotkey/src/update.h"

void update_open(lua_State* L);
void update_push(lua_State* L, struct libhotkey_update update);
struct libhotkey_update* update_get(lua_State* L, int index);
