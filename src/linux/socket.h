#include <stdbool.h>
#include <lua.h>

int socket_init();
void socket_close();
bool socket_push(lua_State* L);
