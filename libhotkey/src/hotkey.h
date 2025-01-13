#pragma once

#include "criteria.h"
#include "update.h"

enum libhotkey_hotkey_type {
	LIBHOTKEY_HOTKEY_KEYSTROKES = 1,
	LIBHOTKEY_HOTKEY_HANDLER = 2
};

struct libhotkey_hotkey {
	enum libhotkey_hotkey_type type;
	struct libhotkey_criteria criteria;
	struct libhotkey_update* keystrokes;
	int keystrokes_length;
	void* extra_data;
};

void libhotkey_hotkey_apply(struct libhotkey_hotkey* hotkey, struct libhotkey_update);

void libhotkey_hotkey_set_handler(void (*handler) (struct libhotkey_hotkey*, struct libhotkey_update));
