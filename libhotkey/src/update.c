#include "update.h"

enum libhotkey_state libhotkey_state_update(enum libhotkey_state initial_state, enum libhotkey_transition transition) {
	switch(transition) {
		case LIBHOTKEY_TRANSITION_PRESS:
			return LIBHOTKEY_STATE_DOWN;
		case LIBHOTKEY_TRANSITION_RELEASE:
			return LIBHOTKEY_STATE_UP;
		case LIBHOTKEY_TRANSITION_AUTOREPEAT:
			return LIBHOTKEY_STATE_DOWN;
	}
}
