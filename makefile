CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2 -flto
BINARY = myshell

all: myshell.o
	$(CC) myshell.o -o myshell -flto

myshell.o: myshell.c
	$(CC) myshell.c $(CFLAGS) -c -o myshell.o

clean:
	rm *.o
