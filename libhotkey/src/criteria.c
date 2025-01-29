#include "criteria-internal.h"

#include <stdbool.h>
#include <stddef.h>

static libhotkey_criteria_handler criteria_handler = NULL;

bool libhotkey_criteria_satisfies(struct libhotkey_criteria* criteria, struct libhotkey_update update) {
	if (criteria->type & LIBHOTKEY_CRITERIA_TRANSITION) {
		if (criteria->transition != update.transition) return false;
	}
	/*
	if (criteria->type & LIBHOTKEY_CRITERIA_KEYSTATE) {
		for (int i = 0; i < criteria->keystates_length; i++) {
			if (libhotkey_keyboard_state(criteria->keystates[i].keycode) != criteria->keystates[i].state)
				return false;
		}
	}
	*/
	if (criteria->type & LIBHOTKEY_CRITERIA_HANDLER) {
		return criteria_handler(criteria, update);
	}

	return true;
}

void libhotkey_set_criteria_handler(libhotkey_criteria_handler handler) {
	criteria_handler = handler;
}
