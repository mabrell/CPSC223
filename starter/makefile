CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: Life
Life: main.c helpers.h life.h helpers.c life.c
	$(CC) $(CFLAGS) -o $@ $^

clean: Life
	rm $^
