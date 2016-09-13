CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2
OBJECTS = shell.o lexer.o

all: $(OBJECTS)
	$(CC) lexer.o shell.o -o shell

shell.o: shell.c shell.h
	$(CC) shell.c $(CFLAGS) -c -o shell.o

lexer.o: lexer.l
	flex lexer.l
	$(CC) lex.yy.c -O2 -c -o lexer.o

clean:
	rm *.o
