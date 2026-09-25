.PHONY: all clean grade-3 grade-4 grade-5 grade-star

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

all: grade-3 grade-4 grade-5 grade-star

grade-3: grade-3/fraction
grade-4: grade-4/fraction
grade-5: grade-5/fraction_dyn
grade-star:
	$(MAKE) -C grade-star

grade-3/fraction:   grade-3/fraction.c
	$(CC) $(CFLAGS) $< -o $@

grade-4/fraction:   grade-4/main.c grade-4/fraction.c grade-4/fraction.h
	$(CC) $(CFLAGS) grade-4/main.c grade-4/fraction.c -o $@

grade-5/fraction_dyn: grade-5/main.c grade-5/fraction.c grade-5/fraction.h
	$(CC) $(CFLAGS) grade-5/main.c grade-5/fraction.c -o $@

clean:
	rm -f grade-3/fraction grade-4/fraction grade-5/fraction_dyn
	$(MAKE) -C grade-star clean
