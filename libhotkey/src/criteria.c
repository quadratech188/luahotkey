#include "criteria.h"

#include <stdbool.h>
#include <stddef.h>

#include "keyboard.h"

static bool (*criteria_handler) (struct libhotkey_criteria*, struct libhotkey_update) = NULL;

bool libhotkey_criteria_satisfies(struct libhotkey_criteria* criteria, struct libhotkey_update update) {
	if (criteria->type & LIBHOTKEY_CRITERIA_TRANSITION) {
		if (criteria->transition != update.transition) return false;
	}
	if (criteria->type & LIBHOTKEY_CRITERIA_KEYSTATE) {
		for (int i = 0; i < criteria->keystates_length; i++) {
			if (libhotkey_keyboard_state(criteria->keystates[i].keycode) != criteria->keystates[i].state)
				return false;
		}
	}
	if (criteria->type & LIBHOTKEY_CRITERIA_HANDLER) {
		return criteria_handler(criteria, update);
	}

	return true;
}

void libhotkey_criteria_set_handler(bool (*handler) (struct libhotkey_criteria*, struct libhotkey_update)) {
	criteria_handler = handler;
}
