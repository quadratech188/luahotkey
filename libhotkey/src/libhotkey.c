#include "libhotkey.h"

#include <stddef.h>

#include "libhotkey-layer.h"
#include "libhotkey-keynode.h"

static libhotkey_output output = NULL;

void libhotkey_send(struct libhotkey_node_ref dest, struct libhotkey_update update) {
	switch(dest.type) {
		case LIBHOTKEY_NODE_NULL:
			output(update);
			break;
		case LIBHOTKEY_NODE_LAYER:
			libhotkey_layer_process(dest.ref, update);
			break;
		case LIBHOTKEY_NODE_KEYNODE:
			libhotkey_keynode_process(dest.ref, update);
	}
}

struct libhotkey_node_ref libhotkey_null_ref() {
	return (struct libhotkey_node_ref) {
		.type = LIBHOTKEY_NODE_NULL,
		.ref = NULL
	};
}

void libhotkey_set_output(libhotkey_output new_output) {
	output = new_output;
}
