#pragma once

#include "libhotkey-action.h"

enum libhotkey_hotkey_flags {
	LIBHOTKEY_HOTKEY_PASSTHROUGH = 1
};

struct libhotkey_hotkey {
	struct libhotkey_criteria* criteria;
	enum libhotkey_hotkey_flags flags;

	int actions_length;
	struct libhotkey_action actions[];
};
