#pragma once

#include "libhotkey.h"

enum libhotkey_action_type {
	LIBHOTKEY_ACTION_PRESS,
	LIBHOTKEY_ACTION_RELEASE,
	LIBHOTKEY_ACTION_AUTOREPEAT,

	LIBHOTKEY_ACTION_MIRROR,

	LIBHOTKEY_ACTION_REQUIRE_DOWN,
	LIBHOTKEY_ACTION_REQUIRE_UP,

	LIBHOTKEY_ACTION_CUSTOM
};

struct libhotkey_action {
	enum libhotkey_action_type type;
	union {
		short keycode;
		void* extra_data;
	};
};

typedef void (*libhotkey_action_handler) (struct libhotkey_action* action, struct libhotkey_update update);
void libhotkey_set_action_handler(libhotkey_action_handler handler);
