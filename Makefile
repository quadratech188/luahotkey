LUA_LIBDIR = /usr/lib64/
LUA_INCDIR = /usr/include/
LIBFLAG = -shared
CFLAGS = -fPIC -g

INCLUDES = -Ilibhotkey/include -I$(LUA_INCDIR)

all: setup libhotkey.so lhk_core.so

setup:
	@mkdir -p build/linux

libhotkey.so:
	cd libhotkey && make all

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=build/%.o)

lhk_core.so: $(OBJECTS) build/linux/io.o build/linux/socket.o
	$(CC) $(LIBFLAG) -o $@ -Llibhotkey -lhotkey -L$(LIBEVDEV_LIBDIR) -levdev $^ \
		-Wl,-rpath,'$$ORIGIN',--version-script=export.map

build/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/linux/io.o: src/linux/io.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ -I$(LIBEVDEV_INCDIR)
build/linux/socket.o: src/linux/socket.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ -I$(LIBEVDEV_INCDIR)

clean:
	rm lhk_core.so build -rf
	cd libhotkey && make $@

install:
	cp lhk_core.so $(INST_LIBDIR)
	cp libhotkey/libhotkey.so $(INST_LIBDIR)
