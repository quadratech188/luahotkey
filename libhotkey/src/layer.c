#include "layer.h"

#include <stdlib.h>

#include "criteria.h"
#include "hotkey.h"
#include "update.h"
#include "update_list.h"
#include "utils/doubly_linked_list.h"

void libhotkey_layer_init(struct libhotkey_layer* layer) {
	for (int i = 0; i < 256; i++) {
		layer->hotkeys[i] = doubly_linked_list_new();
	}
	layer->next_layer = NULL;
}

void libhotkey_layer_apply(struct libhotkey_layer* layer) {
	if (layer == NULL) return;

	libhotkey_update_list_reset();

	while (libhotkey_update_list_advance()) {
		struct libhotkey_update update = libhotkey_update_list_get();

		bool matched = false;

		struct doubly_linked_list_node* ptr = layer->hotkeys[update.keycode].before_begin->next;

		while (ptr != layer->hotkeys[update.keycode].end) {
			struct libhotkey_hotkey* hotkey = ptr->data;
			if (hotkey->criteria == NULL || libhotkey_criteria_satisfies(hotkey->criteria, update)) {
				if (!matched) {
					// TODO: Optimize by using libhotkey_update_list_replace()
					libhotkey_update_list_pop();
					matched = true;
				}
				libhotkey_hotkey_apply(hotkey, update);
			}
			ptr = ptr->next;
		}
	}

	libhotkey_layer_apply(layer->next_layer);
}

void libhotkey_layer_register(struct libhotkey_layer* layer, short keycode, struct libhotkey_hotkey* hotkey) {
	doubly_linked_list_push_right(&layer->hotkeys[keycode], hotkey);
}
