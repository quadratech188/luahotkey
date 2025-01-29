#include "loop.h"

#include <stddef.h>
#include <stdbool.h>

#include "io.h"
#include "libhotkey.h"

static struct libhotkey_node_ref root;
static bool stop = false;

void libhotkey_loop_start() {
	stop = false;

	while (libhotkey_io_await_update()) {
		libhotkey_send(root, libhotkey_io_get_update());
		libhotkey_io_send_update();

		if (stop) break;
	}
}

void libhotkey_loop_stop() {
	stop = true;
}

void libhotkey_loop_set_root(struct libhotkey_node_ref new_root) {
	root = new_root;
}
