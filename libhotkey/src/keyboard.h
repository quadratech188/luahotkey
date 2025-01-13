#pragma once

#include "update.h"
#include "key.h"

void libhotkey_keyboard_init();

struct libhotkey_update libhotkey_keyboard_pop_update();
int libhotkey_keyboard_update_count();

void libhotkey_keyboard_push_update(struct libhotkey_update update);
void libhotkey_keyboard_send_updates();

enum libhotkey_state libhotkey_keyboard_state(short keycode);
