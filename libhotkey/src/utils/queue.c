#include "queue.h"

#include "doubly_linked_list.h"

queue queue_new() {
	return doubly_linked_list_new();
}

void queue_push(queue* queue, void* data) {
	doubly_linked_list_push_right(queue, data);
}

void* queue_front(queue* queue) {
	return doubly_linked_list_left(queue);
}

void queue_pop(queue* queue) {
	doubly_linked_list_pop_left(queue);
}

void queue_free(queue* queue) {
	doubly_linked_list_free(queue);
}
