#pragma once

#include "libhotkey.h"

#include <stdbool.h>

#include "libhotkey-keynode.h"


enum libhotkey_criteria_type {
	LIBHOTKEY_CRITERIA_TRANSITION = 1,
	LIBHOTKEY_CRITERIA_KEYSTATE = 2,
	LIBHOTKEY_CRITERIA_HANDLER = 4
};

struct libhotkey_criteria {
	enum libhotkey_criteria_type type;
	enum libhotkey_transition transition;
	void* extra_data;
	struct libhotkey_keynode* keynode;
	int keystates_length;
	struct libhotkey_keystate keystates[];
};

typedef bool (*libhotkey_criteria_handler) (struct libhotkey_criteria* action, struct libhotkey_update update);
void libhotkey_set_criteria_handler(libhotkey_criteria_handler handler);
