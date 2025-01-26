#include "libhotkey.h"
#include "libhotkey_internal.h"

#include "io.h"
#include "layer.h"

void libhotkey_send(struct libhotkey_node_ref dest, struct libhotkey_update update) {
	switch(dest.type) {
		case LIBHOTKEY_NODE_NULL:
			libhotkey_io_queue_update(update);
			break;
		case LIBHOTKEY_NODE_LAYER:
			libhotkey_send_from_layer(dest.ref, update);
	}
}

struct libhotkey_node_ref libhotkey_ref_to_layer(struct libhotkey_layer* layer) {
	return (struct libhotkey_node_ref) {
		.type = LIBHOTKEY_NODE_LAYER,
		.ref = layer
	};
}

struct libhotkey_node_ref libhotkey_ref_null() {
	return (struct libhotkey_node_ref) {
		.type = LIBHOTKEY_NODE_NULL,
		.ref = NULL
	};
}
