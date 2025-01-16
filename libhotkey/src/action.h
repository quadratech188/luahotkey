#pragma once

#include "update.h"

enum libhotkey_action_type {
	LIBHOTKEY_ACTION_PRESS,
	LIBHOTKEY_ACTION_RELEASE,
	LIBHOTKEY_ACTION_AUTOREPEAT,
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

void libhotkey_action_set_handler(void (*handler) (struct libhotkey_action* action, struct libhotkey_update update));

void libhotkey_action_apply(struct libhotkey_action* action, struct libhotkey_update update);
