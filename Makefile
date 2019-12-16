CXX = gcc
CFLAGS = -std=c11 -Wall
CFLAGS_SHARED = -fPIC -shared

# File size used in page cache eviction
FSIZE = $(shell grep MemTotal /proc/meminfo | awk '{print int($$2/1024)}')

build: libcc.so receiver sender file

libcc.so: covert_channel.c
	$(CXX) $(CFLAGS) $(CFLAGS_SHARED) -o libcc.so covert_channel.c

receiver: receiver.c util.c libcc.so
	$(CXX) -I./ -L./ -o receiver receiver.c util.c -lcc

sender: sender.c util.c libcc.so
	$(CXX) -I./ -L./ -o sender sender.c util.c -lcc

file:
	@echo "Creating a large file. It may take some time."
	dd if=/dev/zero of=file bs=1MB count=$(FSIZE)

run-sender:
	LD_LIBRARY_PATH=. ./sender

run-receiver:
	LD_LIBRARY_PATH=. ./receiver

clean:
	rm -f libcc.so receiver sender *.o file
