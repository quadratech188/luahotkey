#include "update.h"

enum libhotkey_state updated_state(enum libhotkey_state initial_state, enum libhotkey_transition transition) {
	switch(transition) {
		case PRESS:
			return DOWN;
		case RELEASE:
			return UP;
		case AUTOREPEAT:
			return DOWN;
	}
}
