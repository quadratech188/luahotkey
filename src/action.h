#include <lua.h>

void action_open(lua_State* L);

struct libhotkey_action* action_get(lua_State* L, int index);
