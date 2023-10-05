CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

# TO STUDENT: You may add to this file, but there must remain a target named
#   "HookBook" that generates an executable named the same.
all: HookBook

HookBook: hookbook.c pirate_list.c pirate.c libhookbook.c
	$(CC) $(CFLAGS) -o $@ $^


clean: HookBook
	rm -f *.0
	rm -f HookBook
# TODO: You must complete the rule to compile HookBook
