#include "action-internal.h"

#include "libhotkey-keynode.h"
#include "libhotkey.h"

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
			if (libhotkey_keynode_state(action->require.keynode, action->require.keycode)
					!= LIBHOTKEY_STATE_DOWN)
				libhotkey_send(dest, (struct libhotkey_update) {
						action->keycode,
						LIBHOTKEY_TRANSITION_PRESS
						});
			break;
		case LIBHOTKEY_ACTION_REQUIRE_UP:
			if (libhotkey_keynode_state(action->require.keynode, action->require.keycode)
					!= LIBHOTKEY_STATE_UP)
				libhotkey_send(dest, (struct libhotkey_update) {
						action->keycode,
						LIBHOTKEY_TRANSITION_RELEASE
						});
			break;

		//TODO: Only send keystrokes when it's necessary (No idea how)
		case LIBHOTKEY_ACTION_ENFORCE:
			if (libhotkey_keynode_state(action->enforce.reference, action->enforce.keycode)
					== LIBHOTKEY_STATE_DOWN) {
				libhotkey_send(dest, (struct libhotkey_update) {
						action->enforce.keycode,
						LIBHOTKEY_TRANSITION_PRESS
						});
			}
			else {
			 	libhotkey_send(dest, (struct libhotkey_update) {
						action->enforce.keycode,
						LIBHOTKEY_TRANSITION_RELEASE
						});
			}
			break;

		case LIBHOTKEY_ACTION_CUSTOM:
			action_handler(action, update);
	}
}

void libhotkey_set_action_handler(libhotkey_action_handler handler) {
	action_handler = handler;
}
