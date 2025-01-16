#pragma once

#include "criteria.h"
#include "action.h"

struct libhotkey_hotkey {
	struct libhotkey_criteria* criteria;
	int actions_length;
	struct libhotkey_action actions[];
};

void libhotkey_hotkey_apply(struct libhotkey_hotkey* hotkey, struct libhotkey_update update);
