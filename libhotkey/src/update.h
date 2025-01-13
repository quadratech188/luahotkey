#pragma once

#include "key.h"

enum libhotkey_transition {
	PRESS,
	RELEASE,
	AUTOREPEAT
};

struct libhotkey_update {
	short keycode;
	enum libhotkey_transition transition;
};

enum libhotkey_state updated_state(enum libhotkey_state initial_state, enum libhotkey_transition transition);
