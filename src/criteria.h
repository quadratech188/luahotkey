#include <lua.h>

void criteria_open(lua_State* L);

struct libhotkey_criteria* criteria_get(lua_State* L, int index);
