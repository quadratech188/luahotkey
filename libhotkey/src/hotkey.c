#include "hotkey.h"

#include <stdbool.h>

#include "action.h"
#include "keyboard.h"
#include "update.h"

void libhotkey_hotkey_apply(struct libhotkey_hotkey* hotkey, struct libhotkey_update update) {
	for (int i = 0; i < hotkey->actions_length; i++)
		libhotkey_action_apply(&hotkey->actions[i], update);
}
