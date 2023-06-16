CC = gcc
CFLAGS = -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -Werror
HEADER = header.h
.PHONY: clean

all: producer consumer main

producer: producer.c $(HEADER)
	$(CC) $(CFLAGS) producer.c -o producer

consumer: consumer.c $(HEADER)
	$(CC) $(CFLAGS) consumer.c -o consumer

main: main.c $(HEADER)
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f producer consumer main
