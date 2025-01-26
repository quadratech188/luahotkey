#include "layer.h"

#include <stdlib.h>

#include "criteria.h"
#include "hotkey.h"
#include "libhotkey.h"
#include "libhotkey_internal.h"
#include "update.h"

struct libhotkey_layer {
	struct list_item* hotkeys[256];

	struct libhotkey_node_ref next;
};

struct list_item {
	struct libhotkey_hotkey* hotkey;
	struct list_item* next;
};

void libhotkey_layer_init(struct libhotkey_layer* layer) {
	for (int i = 0; i < 256; i++) {
		layer->hotkeys[i] = NULL;
	}
	layer->next.type = LIBHOTKEY_NODE_NULL;
}

void libhotkey_layer_cleanup(struct libhotkey_layer* layer) {
	for (int i = 0; i < 256; i++) {
		struct list_item* ptr = layer->hotkeys[i];

		while (ptr != NULL) {
			struct list_item* next = ptr->next;
			free(ptr);
			ptr = next;
		}
	}
}

void libhotkey_send_from_layer(struct libhotkey_layer* layer, struct libhotkey_update update) {
	struct list_item* ptr = layer->hotkeys[update.keycode];

	bool matched = false;

	while (ptr != NULL) {
		struct libhotkey_hotkey* hotkey = ptr->hotkey;
		if (hotkey->criteria == NULL || libhotkey_criteria_satisfies(hotkey->criteria, update)) {
			if (!matched) {
				matched = true;
			}
			libhotkey_hotkey_apply(layer->next, hotkey, update);
		}
		ptr = ptr->next;
	}

	if (!matched) {
		libhotkey_send(layer->next, update);
	}
}

void libhotkey_layer_register(struct libhotkey_layer* layer, short keycode, struct libhotkey_hotkey* hotkey) {
	struct list_item* prev = layer->hotkeys[keycode];
	layer->hotkeys[keycode] = malloc(sizeof(struct list_item));
	layer->hotkeys[keycode]->hotkey = hotkey;
	layer->hotkeys[keycode]->next = prev;
}

void libhotkey_set_next_node(struct libhotkey_layer* layer, struct libhotkey_node_ref next) {
	layer->next = next;
}

size_t libhotkey_layer_size() {
	return sizeof(struct libhotkey_layer);
}
