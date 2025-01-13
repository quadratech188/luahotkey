#pragma once

struct libhotkey_layer {
	struct libhotkey_layer* next_layer;
};

void libhotkey_layer_apply(struct libhotkey_layer* layer);
