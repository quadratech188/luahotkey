#include "layer.h"

#include <stdlib.h>

#include "criteria.h"
#include "hotkey.h"
#include "update.h"
#include "update_list.h"

struct libhotkey_layer {
	struct list_item* hotkeys[256];
	struct libhotkey_layer* next_layer;
};

struct list_item {
	struct libhotkey_hotkey* hotkey;
	struct list_item* next;
};

void libhotkey_layer_init(struct libhotkey_layer* layer) {
	for (int i = 0; i < 256; i++) {
		layer->hotkeys[i] = NULL;
	}
	layer->next_layer = NULL;
}

void libhotkey_layer_apply(struct libhotkey_layer* layer) {
	if (layer == NULL) return;

	libhotkey_update_list_reset();

	while (libhotkey_update_list_advance()) {
		struct libhotkey_update update = libhotkey_update_list_get();

		bool matched = false;

		struct list_item* ptr = layer->hotkeys[update.keycode];

		while (ptr != NULL) {
			struct libhotkey_hotkey* hotkey = ptr->hotkey;
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
	struct list_item* prev = layer->hotkeys[keycode];
	layer->hotkeys[keycode] = malloc(sizeof(struct list_item));
	layer->hotkeys[keycode]->hotkey = hotkey;
	layer->hotkeys[keycode]->next = prev;
}

void libhotkey_set_next_layer(struct libhotkey_layer* layer, struct libhotkey_layer* next) {
	layer->next_layer = next;
}

size_t libhotkey_layer_size() {
	return sizeof(struct libhotkey_layer);
}
