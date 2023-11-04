#Gmap_makefile

# CC = gcc
# CFLAGS = -std=c17 -Wall -Werror -pedantic -g

# all: GmapUnit

# GmapUnit: gmap_unit.c gmap.c string_key.c gmap_test_functions.c
# 	$(CC) $(CFLAGS) -o $@ $^



# clean: GmapUnit
# 	rm -f *.0
# 	rm -f GmapUnit

#Blotto_makefile

CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: Blotto GmapUnit

GmapUnit: gmap_unit.c gmap.c string_key.c gmap_test_functions.c
	$(CC) $(CFLAGS) -o $@ $^

Blotto: blotto.c libblotto.c gmap.c string_key.c entry.c
	$(CC) $(CFLAGS) -o $@ $^

clean: GmapUnit Blotto
	rm -f *.0
	rm $^


