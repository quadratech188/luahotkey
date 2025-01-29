#include "action-internal.h"

static libhotkey_action_handler action_handler;

void libhotkey_apply_action(struct libhotkey_node_ref dest, struct libhotkey_action* action, struct libhotkey_update update) {
	switch(action->type) {
		case LIBHOTKEY_ACTION_PRESS:
			libhotkey_send(dest, (struct libhotkey_update) {
					action->keycode,
					LIBHOTKEY_TRANSITION_PRESS
					});
			break;
		case LIBHOTKEY_ACTION_RELEASE:
			libhotkey_send(dest, (struct libhotkey_update) {
					action->keycode,
					LIBHOTKEY_TRANSITION_RELEASE
					});
			break;
		case LIBHOTKEY_ACTION_AUTOREPEAT:
			libhotkey_send(dest, (struct libhotkey_update) {
					action->keycode,
					LIBHOTKEY_TRANSITION_AUTOREPEAT
					});
			break;

		case LIBHOTKEY_ACTION_MIRROR:
			libhotkey_send(dest, (struct libhotkey_update) {
					action->keycode,
					update.transition
					});
			break;

		case LIBHOTKEY_ACTION_REQUIRE_DOWN:
			// if (libhotkey_keyboard_state(action->keycode) != LIBHOTKEY_STATE_DOWN)
				libhotkey_send(dest, (struct libhotkey_update) {
						action->keycode,
						LIBHOTKEY_TRANSITION_PRESS
						});
			break;
		case LIBHOTKEY_ACTION_REQUIRE_UP:
			// if (libhotkey_keyboard_state(action->keycode) != LIBHOTKEY_STATE_UP)
				libhotkey_send(dest, (struct libhotkey_update) {
						action->keycode,
						LIBHOTKEY_TRANSITION_RELEASE
						});
			break;
		case LIBHOTKEY_ACTION_CUSTOM:
			action_handler(action, update);
	}
}

void libhotkey_set_action_handler(libhotkey_action_handler handler) {
	action_handler = handler;
}
