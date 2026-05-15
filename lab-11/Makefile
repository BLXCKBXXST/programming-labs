.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

AFTER  := task-1/after task-2/after task-3/after task-4/after

all: $(AFTER)

%/after: %/after.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(AFTER)
