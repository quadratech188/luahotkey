#pragma once

#include "update.h"

enum libhotkey_node_type {
	LIBHOTKEY_NODE_NULL,
	LIBHOTKEY_NODE_LAYER
};

struct libhotkey_node_ref {
	enum libhotkey_node_type type;
	void* ref;
};

void libhotkey_send(struct libhotkey_node_ref dest, struct libhotkey_update update);

#include "layer.h"
struct libhotkey_node_ref libhotkey_ref_to_layer(struct libhotkey_layer* layer);
struct libhotkey_node_ref libhotkey_ref_null();
