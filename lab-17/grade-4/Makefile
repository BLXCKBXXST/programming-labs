.PHONY: all clean run

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../external/tinyexpr
LDLIBS  := -lcmocka -lm

all: test_cmocka

test_cmocka: test_cmocka.c ../external/tinyexpr/tinyexpr.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

run: test_cmocka
	./test_cmocka

clean:
	rm -f test_cmocka
