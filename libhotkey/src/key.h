#pragma once

enum libhotkey_state {
	LIBHOTKEY_STATE_UP,
	LIBHOTKEY_STATE_DOWN
};

struct libhotkey_keystate {
	short keycode;
	enum libhotkey_state state;
};
