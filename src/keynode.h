#include <lua.h>

const char* keynode_metatablename();

void keynode_open(lua_State* L);

struct libhotkey_keynode* keynode_get(lua_State* L, int index);
