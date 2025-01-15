#include "doubly_linked_list.h"

typedef struct doubly_linked_list queue;

queue queue_new();
void queue_push(queue* queue, void* data);
void* queue_front(queue* queue);
void queue_pop(queue* queue);
void queue_poppush(queue* queue);
void queue_free(queue* queue);
