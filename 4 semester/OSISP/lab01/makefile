CC = gcc

CFLAGS = -c -W -Wall -Wextra

.PHONY:all
all: start

start:	lab1.o	
	$(CC) lab1.o -o lab1

lab1.o: lab1.c
	$(CC) $(CFLAGS) lab1.c
	
clean:
	rm -rf *.o lab1
