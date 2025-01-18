#include "loop.h"

#include <stddef.h>
#include <stdbool.h>

#include "io.h"
#include "keyboard.h"
#include "layer.h"
#include "update_list.h"


static struct libhotkey_layer* root;
static bool stop = false;

int libhotkey_loop_start() {
	if (root == NULL) return LIBHOTKEY_NO_ROOT;

	libhotkey_update_list_init();

	while (libhotkey_io_await_update()) {
		libhotkey_update_list_reset();
		libhotkey_update_list_push(libhotkey_io_get_update());
		libhotkey_layer_apply(root);

		if (stop) break;

		libhotkey_update_list_send();
	}

	return 0;
}

void libhotkey_loop_stop() {
	stop = true;
}

void libhotkey_loop_set_root(struct libhotkey_layer* new_root) {
	root = new_root;
}
