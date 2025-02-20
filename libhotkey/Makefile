# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -fPIC -g
LIBFLAG = -shared

SOURCES = $(wildcard src/*.c)

OBJECTS = $(SOURCES:src/%.c=build/%.o)

all: libhotkey.so

libhotkey.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBFLAG) -o $@ $^ -Wl,--version-script=export.map

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -rf build libhotkey.so

.PHONY: all clean
