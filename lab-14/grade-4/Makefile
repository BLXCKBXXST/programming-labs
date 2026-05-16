.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Iinclude

all: sneakers

sneakers: src/main.c src/list.c include/list.h
	$(CC) $(CFLAGS) src/main.c src/list.c -o $@

clean:
	rm -f sneakers
