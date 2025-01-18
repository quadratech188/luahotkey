#include "update_list.h"

#include <stdlib.h>
#include <stdbool.h>

#include "io.h"
#include "keyboard.h"
#include "update.h"

struct listitem {
	struct libhotkey_update update;
	struct listitem* prev;
	struct listitem* next;
};

static struct listitem before_begin;
static struct listitem end;

static struct listitem* current;

static void link(struct listitem* left, struct listitem* right) {
	left->next = right;
	right->prev = left;
}

void libhotkey_update_list_init() {
	link(&before_begin, &end);
	libhotkey_update_list_reset();
}

/*
1(current) -> 2 -> 3
1 -> 2(current) -> 3
*/
bool libhotkey_update_list_advance() {
	current = current->next;
	return current != &end;
}

void libhotkey_update_list_reset() {
	current = &before_begin;
}

struct libhotkey_update libhotkey_update_list_get() {
	return current->update;
}

/*
1(current) -> 2 -> 3
1 -> 4(current) -> 2 -> 3
*/
void libhotkey_update_list_push(struct libhotkey_update update) {
	struct listitem* new = malloc(sizeof(struct listitem));
	new->update = update;
	link(new, current->next);
	link(current, new);
	current = new;
}

void libhotkey_update_list_replace(struct libhotkey_update update) {
	current->update = update;
}

/*
1 -> 2(current) -> 3
1(current) -> 3
*/
void libhotkey_update_list_pop() {
	struct listitem* old = current;
	current = old->prev;
	link(current, old->next);
	free(old);
}

void libhotkey_update_list_send() {
	libhotkey_update_list_reset();

	while (libhotkey_update_list_advance()) {
		libhotkey_io_queue_update(current->update);
		libhotkey_update_list_pop();
	}
	libhotkey_io_send_update();
}
