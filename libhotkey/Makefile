# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -fPIC -g
LIBFLAG = -shared

# Directories
SRC_DIR = src
BUILD_DIR = build
UTILS_DIR = $(SRC_DIR)/utils
INCLUDE_DIR = include

# Source files
COMMON_SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Object files
COMMON_OBJECTS = $(COMMON_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/src/%.o)

# Target
TARGET = libhotkey.so

# Rules
all: $(TARGET)

$(TARGET): $(COMMON_OBJECTS) $(PLATFORM_OBJECTS)
	$(CC) $(CFLAGS) $(LIBFLAG) -o $@ $^ -Wl,--version-script=export.map

$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
