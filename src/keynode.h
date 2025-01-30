#include <lua.h>

void keynode_open(lua_State* L);

struct libhotkey_keynode* keynode_get(lua_State* L, int index);
struct libhotkey_keynode* keynode_test(lua_State* L, int index);
