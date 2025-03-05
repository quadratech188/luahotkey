#include "io.h"

#include "../settings.h"

#include "libevdev/libevdev.h"
#include "libevdev/libevdev-uinput.h"
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "linux_utils.h"

static struct libevdev* input_dev = NULL;

static struct libevdev* output_dev = NULL;
static struct libevdev_uinput* output_uidev = NULL;

static struct input_event event;

int io_init() {
	// input
	// https://www.freedesktop.org/software/libevdev/doc/latest/
	int input_fd = open(settings_input(), O_RDWR);

	if (input_fd < 0) {
		io_cleanup();
		return LIBHOTKEY_OPEN_INPUT_FAIL;
	}

	int result = libevdev_new_from_fd(input_fd, &input_dev);

	if (result < 0) {
		io_cleanup();
		return LIBHOTKEY_OPEN_INPUT_FAIL;
	}

	// Wait until all keys are released
	char keys[KEY_MAX/8 + 1];
	memset(keys, 0, sizeof(keys));

	bool all_released = false;

	while (!all_released) {
		// TODO: Obviously inefficient
		ioctl(libevdev_get_fd(input_dev), EVIOCGKEY(sizeof(keys)), keys);

		all_released = true;
		for (int i = 0; i < sizeof(keys); i++) {
			if (keys[i] != 0) all_released = false;
		}
		libevdev_next_event(input_dev, LIBEVDEV_READ_FLAG_BLOCKING, &event);
	}

	if (settings_grab()) {
		result = libevdev_grab(input_dev, LIBEVDEV_GRAB);

		if (result < 0) {
			io_cleanup();
			return LIBHOTKEY_GRAB_INPUT_FAIL;
		}
	}

	// output
	output_dev = libevdev_new();
	libevdev_set_name(output_dev, settings_output());

	// Enable enough events for programs to recognize us as a keyboard
	libevdev_enable_event_type(output_dev, EV_SYN);
	libevdev_enable_event_type(output_dev, EV_KEY);
	libevdev_enable_event_type(output_dev, EV_MSC);
	libevdev_enable_event_type(output_dev, EV_LED);
	libevdev_enable_event_type(output_dev, EV_REP);

	// Enable all the keys
	for (int i = 0; i < 256; i++) {
		libevdev_enable_event_code(output_dev, EV_KEY, i, NULL);
	}

	result = libevdev_uinput_create_from_device(output_dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &output_uidev);

	if (result < 0) {
		io_cleanup();
		return LIBHOTKEY_CREATE_OUTPUT_FAIL;
	}

	return 0;
}

bool io_await_update() {
	do {
		int result = libevdev_next_event(input_dev, LIBEVDEV_READ_FLAG_BLOCKING, &event);

		if (result < 0) {
			io_cleanup();
			return false;
		}
	} while (event.type != EV_KEY);

	return true;
}

struct libhotkey_update io_get_update() {
	return (struct libhotkey_update) {
		.keycode = event.code,
		.transition = event_value_to_transition(event.value)
	};
}

void io_queue_update(struct libhotkey_update update) {
	libevdev_uinput_write_event(output_uidev,
			EV_KEY,
			update.keycode,
			transition_to_event_value(update.transition));
}

void io_sync_updates() {
	libevdev_uinput_write_event(output_uidev, EV_SYN, SYN_REPORT, 0);
}

void io_cleanup() {
	libevdev_uinput_destroy(output_uidev);
	if (input_dev) {
		int input_fd = libevdev_get_fd(input_dev);
		libevdev_grab(input_dev, LIBEVDEV_UNGRAB);
		libevdev_free(input_dev);
		close(input_fd);
	}
	if (output_dev) {
		libevdev_free(output_dev);
	}
}
