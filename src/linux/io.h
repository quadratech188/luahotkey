#include <stdbool.h>

#include "libhotkey.h"

#define LIBHOTKEY_OPEN_INPUT_FAIL 1
#define LIBHOTKEY_GRAB_INPUT_FAIL 2
#define LIBHOTKEY_CREATE_OUTPUT_FAIL 3


int io_init();

bool io_await_update();
struct libhotkey_update io_get_update();

void io_queue_update(struct libhotkey_update update);
void io_sync_updates();

void io_cleanup();
