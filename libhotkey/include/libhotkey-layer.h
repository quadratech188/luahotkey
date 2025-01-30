#pragma once

#include "libhotkey-hotkey.h"
#include "libhotkey.h"

struct libhotkey_layer;

int libhotkey_layer_size();

void libhotkey_layer_init(struct libhotkey_layer* layer);
void libhotkey_layer_cleanup(struct libhotkey_layer* layer);
void libhotkey_layer_set_next(struct libhotkey_layer* layer, struct libhotkey_node_ref next);
void libhotkey_register_hotkey(struct libhotkey_layer* layer, short keycode, struct libhotkey_hotkey* hotkey);

void libhotkey_layer_process(struct libhotkey_layer* layer, struct libhotkey_update update);

struct libhotkey_node_ref libhotkey_layer_ref(struct libhotkey_layer* layer);
