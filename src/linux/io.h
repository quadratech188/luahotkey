#include <stdbool.h>

#include "libhotkey.h"

#define LIBHOTKEY_OPEN_INPUT_FAIL 1
#define LIBHOTKEY_GRAB_INPUT_FAIL 2
#define LIBHOTKEY_CREATE_OUTPUT_FAIL 3


int libhotkey_io_init();

bool libhotkey_io_await_update();
struct libhotkey_update libhotkey_io_get_update();

void libhotkey_io_queue_update(struct libhotkey_update update);
void libhotkey_io_send_update();

void libhotkey_io_cleanup();
