LUA_LIBDIR = /usr/lib64/
LUA_INCDIR = /usr/include/
LIBFLAG = -shared
CFLAGS = -fPIC -g

all: build libhotkey.so lhk_core.so

libhotkey.so:
	cd libhotkey && make all

build:
	mkdir -p build

lhk_core.so: build/main.o build/layer.o build/criteria.o build/hotkey.o build/enums.o build/keystate.o build/update.o
	$(CC) $(LIBFLAG) -o $@ -Llibhotkey -lhotkey $^ -Wl,-rpath,'$$ORIGIN'

build/main.o: src/main.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/layer.o: src/layer.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/criteria.o: src/criteria.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/hotkey.o: src/hotkey.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/enums.o: src/enums.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/keystate.o: src/keystate.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

build/update.o: src/update.c
	$(CC) -c $(CFLAGS) -I$(LUA_INCDIR) $< -o $@

clean:
	rm lhk_core.so build -rf
	cd libhotkey && make $@

install:
	cp lhk_core.so $(INST_LIBDIR)
	cp libhotkey/libhotkey.so $(INST_LIBDIR)
