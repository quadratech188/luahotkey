#include "../update.h"

enum libhotkey_transition event_value_to_transition(unsigned int event_value) {
	switch(event_value) {
		case 0:
			return RELEASE;
		case 1:
			return PRESS;
		case 2:
			return AUTOREPEAT;
	}
}

unsigned int transition_to_event_value(enum libhotkey_transition transition) {
	switch(transition) {
		case PRESS:
			return 1;
		case RELEASE:
			return 0;
		case AUTOREPEAT:
			return 2;
	}
}
