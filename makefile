CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g
all: HelloWorld HelloJack
HelloWorld: hello_1.c
	$(CC) $(CFLAGS) -o $@ hello_1.c
HelloJack: hello_2.c
	$(CC) $(CFLAGS) -o $@ hello_2.c
clean: HelloWorld HelloJack
	rm $^