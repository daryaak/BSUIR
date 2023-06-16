CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -W -pthread

.PHONY: clean
all: generator sort_index

generate: $(GENERATOR) header.h
	$(CC) $(CFLAGS) generator.c -o generator

sort_index: $(SORTER) header.h
	$(CC) $(CFLAGS) sort_index.c -o sort_index

clean:
	rm -f generator sort_index file.bin sorted.bin buffer.bin