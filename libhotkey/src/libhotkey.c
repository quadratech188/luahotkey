#include "libhotkey.h"
#include "libhotkey_internal.h"

#include "io.h"

static struct libhotkey_layer* active_layer;

void libhotkey_set_active_layer(struct libhotkey_layer* layer) {
	active_layer = layer;
}

void libhotkey_send(struct libhotkey_update update) {
	if (active_layer == NULL)
		libhotkey_io_queue_update(update);
	else
		libhotkey_send_from_layer(active_layer, update);
}
