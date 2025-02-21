#pragma once

#include "libhotkey.h"

enum libhotkey_action_type {
	LIBHOTKEY_ACTION_PRESS,
	LIBHOTKEY_ACTION_RELEASE,
	LIBHOTKEY_ACTION_AUTOREPEAT,

	LIBHOTKEY_ACTION_MIRROR,

	LIBHOTKEY_ACTION_REQUIRE_DOWN,
	LIBHOTKEY_ACTION_REQUIRE_UP,

	LIBHOTKEY_ACTION_ENFORCE,
	LIBHOTKEY_ACTION_ENFORCE_FROM_DOWN,
	LIBHOTKEY_ACTION_ENFORCE_FROM_UP,

	LIBHOTKEY_ACTION_LAYER_SET_NEXT,
	LIBHOTKEY_ACTION_KEYNODE_SET_NEXT,

	LIBHOTKEY_ACTION_CUSTOM
};

struct libhotkey_action {
	enum libhotkey_action_type type;
	union {
		short keycode;
		void* extra_data;
		struct {
			short keycode;
			struct libhotkey_keynode* keynode;
		} require;
		struct {
			short keycode;
			struct libhotkey_keynode* reference;
		} enforce;
		struct {
			struct libhotkey_layer* layer;
			struct libhotkey_node_ref ref;
		} layer_set_next;
		struct {
			struct libhotkey_keynode* keynode;
			struct libhotkey_node_ref ref;
		} keynode_set_next;
	};
};

typedef void (*libhotkey_action_handler) (struct libhotkey_action* action, struct libhotkey_update update);
void libhotkey_set_action_handler(libhotkey_action_handler handler);
