#pragma once

enum libhotkey_state {
	LIBHOTKEY_STATE_UP,
	LIBHOTKEY_STATE_DOWN
};

struct libhotkey_keystate {
	short keycode;
	enum libhotkey_state state;
};

enum libhotkey_transition {
	LIBHOTKEY_TRANSITION_PRESS,
	LIBHOTKEY_TRANSITION_RELEASE,
	LIBHOTKEY_TRANSITION_AUTOREPEAT
};

struct libhotkey_update {
	short keycode;
	enum libhotkey_transition transition;
};

enum libhotkey_node_type {
	LIBHOTKEY_NODE_NULL,
	LIBHOTKEY_NODE_LAYER,
	LIBHOTKEY_NODE_KEYNODE
};

struct libhotkey_node_ref {
	enum libhotkey_node_type type;
	void* ref;
};

struct libhotkey_node_ref libhotkey_null_ref();

void libhotkey_send(struct libhotkey_node_ref dest, struct libhotkey_update update);

typedef void (*libhotkey_output)(struct libhotkey_update update);

void libhotkey_set_output(libhotkey_output output);
