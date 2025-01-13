#include "doubly_linked_list.h"

#include <stdlib.h>

static struct doubly_linked_list_node* new_node(void* data) {
	struct doubly_linked_list_node* node = malloc(sizeof(struct doubly_linked_list_node));
	node->data = data;
	return node;
}

static void link(struct doubly_linked_list_node* left, struct doubly_linked_list_node* right) {
	left->next = right;
	right->prev = left;
}

struct doubly_linked_list doubly_linked_list_new() {
	struct doubly_linked_list_node* before_begin = new_node(NULL);
	struct doubly_linked_list_node* end = new_node(NULL);
	link(before_begin, end);

	return (struct doubly_linked_list) {
		.before_begin = before_begin,
		.end = end,
		.size = 0
	};
}

void* doubly_linked_list_left(struct doubly_linked_list* list) {
	return list->before_begin->next->data;
}

void doubly_linked_list_pop_left(struct doubly_linked_list* list) {
	struct doubly_linked_list_node* left = list->before_begin->next;
	link(list->before_begin, left->next);
	free(left);

	list->size--;
}

void doubly_linked_list_push_left(struct doubly_linked_list* list, void* data) {
	struct doubly_linked_list_node* left = new_node(data);
	link(left, list->before_begin->next);
	link(list->before_begin, left);

	list->size++;
}

void* doubly_linked_list_right(struct doubly_linked_list* list) {
	return list->end->prev->data;
}

void doubly_linked_list_pop_right(struct doubly_linked_list* list) {
	struct doubly_linked_list_node* right = list->end->prev;
	link(right->prev, list->end);
	free(right);

	list->size--;
}

void doubly_linked_list_push_right(struct doubly_linked_list* list, void* data) {
	struct doubly_linked_list_node* right = new_node(data);
	link(list->end->prev, right);
	link(right, list->end);

	list->size++;
}

void doubly_linked_list_free(struct doubly_linked_list* list) {
	free(list->before_begin);
	free(list->end);
}
