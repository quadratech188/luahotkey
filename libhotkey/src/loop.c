#include "loop.h"

#include <stddef.h>
#include <stdbool.h>

#include "layer.h"
#include "keyboard.h"
#include "io.h"


static struct libhotkey_layer* root;
static bool stop = false;

int libhotkey_loop_start() {
	if (root == NULL) return LIBHOTKEY_NO_ROOT;

	libhotkey_keyboard_init();

	while (libhotkey_io_await_update()) {
		struct libhotkey_update transition = libhotkey_io_get_update();

		libhotkey_keyboard_push_update(transition);

		libhotkey_layer_apply(root);

		if (stop) break;

		libhotkey_keyboard_send_updates();
	}

	return 0;
}

void libhotkey_loop_stop() {
	stop = true;
}

void libhotkey_loop_set_root(struct libhotkey_layer* new_root) {
	root = new_root;
}
