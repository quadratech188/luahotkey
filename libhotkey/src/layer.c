#include "layer.h"

#include <stdlib.h>

#include "keyboard.h"
#include "update.h"

void libhotkey_layer_apply(struct libhotkey_layer* layer) {
	int update_count = libhotkey_keyboard_update_count();
	for (int i = 0; i < update_count; i++) {
		struct libhotkey_update update = libhotkey_keyboard_pop_update();

		/*
		if (update.keycode == 32) {
			libhotkey_keyboard_push_update((struct libhotkey_update){
					.keycode = 33,
					.transition = PRESS
					});
			libhotkey_keyboard_push_update((struct libhotkey_update){
					.keycode = 33,
					.transition = RELEASE
					});
		}
		*/

		libhotkey_keyboard_push_update(update);
	}

	if (layer->next_layer != NULL)
		libhotkey_layer_apply(layer->next_layer);
}
