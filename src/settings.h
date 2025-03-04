#include <stdbool.h>
#include <lua.h>

void settings_open(lua_State* L);

bool settings_grab();
const char* settings_input();
const char* settings_output();
const char* settings_socket();
void settings_push_socket_handler(lua_State* L);
bool settings_use_socket();
