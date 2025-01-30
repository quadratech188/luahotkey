#include "libhotkey-keynode.h"
#include "libhotkey.h"

struct libhotkey_keynode {
	enum libhotkey_state states[256];

	struct libhotkey_node_ref next;
};

int libhotkey_keynode_size() {
	return sizeof(struct libhotkey_keynode);
}

void libhotkey_keynode_init(struct libhotkey_keynode* keynode) {
	for (int i = 0; i < 256; i++) {
		keynode->states[i] = LIBHOTKEY_STATE_UP;
	}
	keynode->next = libhotkey_null_ref();
}

void libhotkey_keynode_process(struct libhotkey_keynode* keynode, struct libhotkey_update update) {
	switch(update.transition) {
		case LIBHOTKEY_TRANSITION_PRESS:
		case LIBHOTKEY_TRANSITION_AUTOREPEAT:
			keynode->states[update.keycode] = LIBHOTKEY_STATE_DOWN;
			break;
		case LIBHOTKEY_TRANSITION_RELEASE:
			keynode->states[update.keycode] = LIBHOTKEY_STATE_UP;
	}
	libhotkey_send(keynode->next, update);
}

void libhotkey_keynode_set_next(struct libhotkey_keynode* keynode, struct libhotkey_node_ref next) {
	keynode->next = next;
}

struct libhotkey_node_ref libhotkey_keynode_ref(struct libhotkey_keynode* keynode) {
	return (struct libhotkey_node_ref) {
		.type = LIBHOTKEY_NODE_KEYNODE,
		.ref = keynode
	};
}

enum libhotkey_state libhotkey_keynode_state(struct libhotkey_keynode* keynode, short keycode) {
	return keynode->states[keycode];
}
