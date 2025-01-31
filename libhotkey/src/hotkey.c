#include "hotkey-internal.h"

#include <stdbool.h>

#include "action-internal.h"
#include "libhotkey-hotkey.h"

void libhotkey_apply_hotkey(struct libhotkey_node_ref dest, struct libhotkey_hotkey* hotkey, struct libhotkey_update update) {
	for (int i = 0; i < hotkey->actions_length; i++)
		libhotkey_apply_action(dest, &hotkey->actions[i], update);

	if (hotkey->flags & LIBHOTKEY_HOTKEY_PASSTHROUGH)
		libhotkey_send(dest, update);
}
