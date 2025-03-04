#include <lauxlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "../settings.h"

int fd;

int socket_init() {
	fd = open(settings_socket(), O_RDONLY | O_NONBLOCK);
	if (fd < 0) return fd;
	return 0;
}

bool socket_push(lua_State* L) {
	static char buffer[512];
	ssize_t size;

	size = read(fd, buffer, 512);

	if (size <= 0) return false;

	luaL_Buffer b;
	luaL_buffinit(L, &b);

	do {
		luaL_addlstring(&b, buffer, size);
	} while ((size = read(fd, buffer, 512)) > 0);

	luaL_pushresult(&b);
	return true;
}
