CC = gcc
CFLAGS = -W -Wall -Wextra -std=c11
HEADER = header.h
.PHONY: clean
all: server client

server: server.c makefile $(HEADER)
	$(CC) $(CFLAGS) server.c -o server
client: client.c makefile $(HEADER)
	$(CC) $(CFLAGS) client.c -o client
clean:
	rm -f server client
