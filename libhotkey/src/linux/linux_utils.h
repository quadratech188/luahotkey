#include "../update.h"

enum libhotkey_transition event_value_to_transition(unsigned int event_value) {
	switch(event_value) {
		case 0:
			return LIBHOTKEY_TRANSITION_RELEASE;
		case 1:
			return LIBHOTKEY_TRANSITION_PRESS;
		case 2:
			return LIBHOTKEY_TRANSITION_AUTOREPEAT;
	}
}

unsigned int transition_to_event_value(enum libhotkey_transition transition) {
	switch(transition) {
		case LIBHOTKEY_TRANSITION_PRESS:
			return 1;
		case LIBHOTKEY_TRANSITION_RELEASE:
			return 0;
		case LIBHOTKEY_TRANSITION_AUTOREPEAT:
			return 2;
	}
}
