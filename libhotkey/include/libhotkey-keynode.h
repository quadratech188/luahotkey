#include "libhotkey.h"

struct libhotkey_keynode;

int libhotkey_keynode_size();
void libhotkey_keynode_init(struct libhotkey_keynode* keynode);

void libhotkey_keynode_process(struct libhotkey_keynode* keynode, struct libhotkey_update update);

void libhotkey_keynode_set_next(struct libhotkey_keynode* keynode, struct libhotkey_node_ref next);

enum libhotkey_state libhotkey_keynode_state(struct libhotkey_keynode* keynode, short keycode);

struct libhotkey_node_ref libhotkey_keynode_ref(struct libhotkey_keynode* keynode);
