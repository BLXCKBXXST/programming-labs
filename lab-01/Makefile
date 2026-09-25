.PHONY: all clean grade-3 grade-4 grade-5

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

all: grade-3 grade-4

grade-3: grade-3/leap
grade-4: grade-4/temperature
grade-5: grade-5/area

grade-3/leap:        grade-3/leap.c        ; $(CC) $(CFLAGS) $< -o $@
grade-4/temperature: grade-4/temperature.c ; $(CC) $(CFLAGS) $< -o $@
grade-5/area:        grade-5/area.c        ; $(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -f grade-3/leap grade-4/temperature grade-5/area
