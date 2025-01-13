#pragma once

enum libhotkey_state {
	UP,
	DOWN
};

struct libhotkey_keystate {
	short keycode;
	enum libhotkey_state state;
};
