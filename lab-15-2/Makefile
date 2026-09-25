.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -g -fsanitize=address,undefined
LDLIBS  :=

BINS := src/task1 src/task2 src/task3 src/task4 src/task5 src/task_star

all: $(BINS)

src/task5:     LDLIBS = -lm
src/task_star: LDLIBS = -lm

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(BINS)
