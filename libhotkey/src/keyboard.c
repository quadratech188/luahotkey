#include "keyboard.h"
#include "utils/queue.h"
#include "io.h"

#include <stdlib.h>

// initialied to down
static enum libhotkey_state actual_state[256];
static enum libhotkey_state state[256];

static queue updates;

void libhotkey_keyboard_init() {
	updates = queue_new();
}

struct libhotkey_update libhotkey_keyboard_get_update() {
	return *(struct libhotkey_update*)queue_front(&updates);
}

struct libhotkey_update libhotkey_keyboard_pop_update() {
	struct libhotkey_update* result_ptr = queue_front(&updates);
	queue_pop(&updates);

	struct libhotkey_update result = *result_ptr;
	free(result_ptr);
	return result;
}

void libhotkey_keyboard_poppush_update() {
	queue_poppush(&updates);
}

int libhotkey_keyboard_update_count() {
	return updates.size;
}

void libhotkey_keyboard_push_update(const struct libhotkey_update update) {
	state[update.keycode] = libhotkey_state_update(state[update.keycode], update.transition);

	struct libhotkey_update* update_ptr = malloc(sizeof(struct libhotkey_update));
	*update_ptr = update;

	queue_push(&updates, update_ptr);
}

void libhotkey_keyboard_send_updates() {
	while (updates.size != 0) {
		libhotkey_io_queue_update(libhotkey_keyboard_pop_update());
	}
	libhotkey_io_send_update();
}

enum libhotkey_state libhotkey_keyboard_state(short keycode) {
	return state[keycode];
}
