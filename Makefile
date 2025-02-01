LUA_LIBDIR = /usr/lib64/
LUA_INCDIR = /usr/include/
LIBFLAG = -shared
CFLAGS = -fPIC -g

INCLUDES = -Ilibhotkey/include -I$(LUA_INCDIR)

all: build libhotkey.so lhk_core.so

libhotkey.so:
	cd libhotkey && make all

build:
	mkdir -p build

lhk_core.so: build/main.o build/layer.o build/criteria.o build/hotkey.o build/enums.o build/keystate.o build/update.o build/action.o build/node_ref.o build/keynode.o build/io.o
	$(CC) $(LIBFLAG) -o $@ -Llibhotkey -lhotkey -L$(LIBEVDEV_LIBDIR) -levdev $^ -Wl,-rpath,'$$ORIGIN' 
build/main.o: src/main.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/layer.o: src/layer.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/criteria.o: src/criteria.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/hotkey.o: src/hotkey.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/enums.o: src/enums.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/keystate.o: src/keystate.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/update.o: src/update.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/action.o: src/action.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/node_ref.o: src/node_ref.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/keynode.o: src/keynode.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

build/io.o: src/linux/io.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ -I$(LIBEVDEV_INCDIR)

clean:
	rm lhk_core.so build -rf
	cd libhotkey && make $@

install:
	cp lhk_core.so $(INST_LIBDIR)
	cp libhotkey/libhotkey.so $(INST_LIBDIR)
