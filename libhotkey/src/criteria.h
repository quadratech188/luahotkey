#pragma once

#include <stdbool.h>

#include "key.h"
#include "update.h"

enum libhotkey_criteria_type {
	LIBHOTKEY_CRITERIA_TRANSITION = 1,
	LIBHOTKEY_CRITERIA_KEYSTATE = 2,
	LIBHOTKEY_CRITERIA_HANDLER = 4
};

struct libhotkey_criteria {
	enum libhotkey_criteria_type type;
	enum libhotkey_transition transition;
	struct libhotkey_keystate* keystates;
	int keystates_length;
	void* extra_data;
};

bool libhotkey_criteria_satisfies(struct libhotkey_criteria* criteria, struct libhotkey_update update);

void libhotkey_criteria_set_handler(bool (*handler) (struct libhotkey_criteria*, struct libhotkey_update));
