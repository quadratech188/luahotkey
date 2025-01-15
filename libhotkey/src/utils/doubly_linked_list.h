#pragma once

struct doubly_linked_list_node {
	struct doubly_linked_list_node* prev;
	struct doubly_linked_list_node* next;
	void* data;
};

struct doubly_linked_list {
	struct doubly_linked_list_node* before_begin;
	struct doubly_linked_list_node* end;
	int size;
};

struct doubly_linked_list doubly_linked_list_new();

void* doubly_linked_list_left(struct doubly_linked_list* list);
void doubly_linked_list_pop_left(struct doubly_linked_list* list);
void doubly_linked_list_push_left(struct doubly_linked_list* list, void* data);

void* doubly_linked_list_right(struct doubly_linked_list* list);
void doubly_linked_list_pop_right(struct doubly_linked_list* list);
void doubly_linked_list_push_right(struct doubly_linked_list* list, void* data);
void doubly_linked_list_free(struct doubly_linked_list* list);
void doubly_linked_list_pop_left_push_right(struct doubly_linked_list* list);
