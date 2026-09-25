.PHONY: all clean grade-4 grade-5 grade-star

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

all: grade-4 grade-5 grade-star

grade-4:    grade-4/square
grade-5:    grade-5/stairs
grade-star: grade-star/spiral

grade-4/square:      grade-4/square.c      ; $(CC) $(CFLAGS) $< -o $@
grade-5/stairs:      grade-5/stairs.c      ; $(CC) $(CFLAGS) $< -o $@
grade-star/spiral:   grade-star/spiral.c   ; $(CC) $(CFLAGS) $< -o $@

clean:
	rm -f grade-4/square grade-5/stairs grade-star/spiral
