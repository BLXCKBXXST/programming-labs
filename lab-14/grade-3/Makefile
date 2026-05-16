.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

all: sneakers

sneakers: main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f sneakers
