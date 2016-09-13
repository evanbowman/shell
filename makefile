CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2 

all: shell.o
	$(CC) shell.o -o shell

shell.o: shell.c shell.h
	$(CC) shell.c $(CFLAGS) -c -o shell.o

clean:
	rm *.o
