#include "hotkey.h"

#include <stdbool.h>

#include "keyboard.h"
#include "update.h"

static void (*hotkey_handler) (struct libhotkey_hotkey*, struct libhotkey_update);

void libhotkey_hotkey_apply(struct libhotkey_hotkey* hotkey, struct libhotkey_update update) {
	if (hotkey->type & LIBHOTKEY_HOTKEY_KEYSTROKES) {
		for (int i = 0; i < hotkey->keystrokes_length; i++)
			libhotkey_keyboard_push_update(hotkey->keystrokes[i]);
	}
	if (hotkey->type & LIBHOTKEY_HOTKEY_HANDLER) {
		hotkey_handler(hotkey, update);
	}
}

void libhotkey_hotkey_set_handler(void (*handler) (struct libhotkey_hotkey*, struct libhotkey_update)) {
	hotkey_handler = handler;
}

