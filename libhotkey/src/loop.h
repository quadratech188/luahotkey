#include "layer.h"

#define LIBHOTKEY_NO_ROOT 1

int libhotkey_loop_start();
void libhotkey_loop_stop();

void libhotkey_loop_set_root(struct libhotkey_layer* root);
