#pragma once

#include "key.h"

enum libhotkey_transition {
	LIBHOTKEY_TRANSITION_PRESS,
	LIBHOTKEY_TRANSITION_RELEASE,
	LIBHOTKEY_TRANSITION_AUTOREPEAT
};

struct libhotkey_update {
	short keycode;
	enum libhotkey_transition transition;
};

enum libhotkey_state libhotkey_state_update(enum libhotkey_state initial_state, enum libhotkey_transition transition);
