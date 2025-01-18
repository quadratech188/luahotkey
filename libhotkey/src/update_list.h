#include <stdbool.h>

void libhotkey_update_list_init();

bool libhotkey_update_list_advance();
void libhotkey_update_list_reset();
struct libhotkey_update libhotkey_update_list_get();

void libhotkey_update_list_push(struct libhotkey_update update);
void libhotkey_update_list_replace(struct libhotkey_update update);
void libhotkey_update_list_pop();
void libhotkey_update_list_send();
