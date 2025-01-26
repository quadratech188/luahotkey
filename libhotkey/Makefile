# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -fPIC -g
LIBFLAG = -shared

# Directories
SRC_DIR = src
BUILD_DIR = build
LINUX_DIR = $(SRC_DIR)/linux
UTILS_DIR = $(SRC_DIR)/utils
INCLUDE_DIR = include

# Source files
COMMON_SOURCES = $(wildcard $(SRC_DIR)/*.c) \
                 $(wildcard $(UTILS_DIR)/*.c)
LINUX_SOURCES = $(wildcard $(LINUX_DIR)/*.c)

# Object files
COMMON_OBJECTS = $(COMMON_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/src/%.o)
LINUX_OBJECTS = $(LINUX_SOURCES:$(LINUX_DIR)/%.c=$(BUILD_DIR)/src/linux/%.o)

# Platform-specific setup
ifeq ($(shell uname -s),Linux)
    PLATFORM_OBJECTS = $(LINUX_OBJECTS)
    LINUX_CFLAGS := $(shell pkg-config --cflags libevdev)
    LIBS := $(shell pkg-config --libs libevdev)
else
    PLATFORM_OBJECTS =
    LINUX_CFLAGS =
    LIBS =
endif

# Target
TARGET = libhotkey.so

# Rules
all: $(TARGET)

$(TARGET): $(COMMON_OBJECTS) $(PLATFORM_OBJECTS)
	$(CC) $(CFLAGS) $(LIBFLAG) -o $@ $^ $(LIBS)

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/src/linux/%.o: $(LINUX_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LINUX_CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
