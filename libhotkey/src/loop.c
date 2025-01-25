#include "loop.h"

#include <stddef.h>
#include <stdbool.h>

#include "io.h"
#include "layer.h"
#include "libhotkey.h"
#include "libhotkey_internal.h"


static struct libhotkey_layer* root;
static bool stop = false;

void libhotkey_loop_start() {
	stop = false;

	while (libhotkey_io_await_update()) {
		libhotkey_set_active_layer(root);
		libhotkey_send(libhotkey_io_get_update());
		libhotkey_io_send_update();

		if (stop) break;
	}
}

void libhotkey_loop_stop() {
	stop = true;
}

void libhotkey_loop_set_root(struct libhotkey_layer* new_root) {
	root = new_root;
}
