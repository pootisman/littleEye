CC=gcc
CFLAGS= -Wall -pedantic -std=c89
DEBUG_FLAGS= -g -p -O0
RELEASE_FLAGS= -s -O2
OBJECTS= src/leye_rem_main.o
APP_BINARY= bin/leye
APP_BINARY_DBG= bin/leye_dbg

all: release debug

release: $(OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(OBJECTS) -o $(APP_BINARY)
debug:
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJECTS) -o $(APP_BINARY_DBG)
clean:
	rm src/*.o
