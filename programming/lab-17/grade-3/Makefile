.PHONY: all clean run

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../external/tinyexpr
LDLIBS  := -lm

all: test_simple

test_simple: test_simple.c ../external/tinyexpr/tinyexpr.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

run: test_simple
	./test_simple

clean:
	rm -f test_simple
