#include <lua.h>

enum libhotkey_state state_get(lua_State* L, int index);
enum libhotkey_transition transition_get(lua_State* L, int index);
