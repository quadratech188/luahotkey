#pragma once

#include "hotkey.h"
#include <stddef.h>

struct libhotkey_layer;

void libhotkey_layer_init(struct libhotkey_layer* layer);
void libhotkey_layer_cleanup(struct libhotkey_layer* layer);

void libhotkey_layer_apply(struct libhotkey_layer* layer);
void libhotkey_layer_register(struct libhotkey_layer* layer, short keycode, struct libhotkey_hotkey* hotkey);
void libhotkey_set_next_layer(struct libhotkey_layer* layer, struct libhotkey_layer* next);
size_t libhotkey_layer_size();
