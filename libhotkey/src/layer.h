#pragma once

#include "utils/doubly_linked_list.h"

struct libhotkey_layer {
	struct doubly_linked_list hotkeys[256];

	struct libhotkey_layer* next_layer;
};

void libhotkey_layer_init(struct libhotkey_layer* layer);
void libhotkey_layer_apply(struct libhotkey_layer* layer);
void libhotkey_layer_apply(struct libhotkey_layer* layer);
