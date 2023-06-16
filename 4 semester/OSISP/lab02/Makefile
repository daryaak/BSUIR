CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic
.PHONY: clean

all: parent.o child.o
parent.o: parent.c Makefile
	$(CC) $(CFLAGS) parent.c -o parent
child.o: child.c Makefile
	$(CC) $(CFLAGS) child.c -o child
clean:
	rm -f parent child
