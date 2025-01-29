#pragma once

#include "libhotkey-action.h"

struct libhotkey_hotkey {
	struct libhotkey_criteria* criteria;
	int actions_length;
	struct libhotkey_action actions[];
};
