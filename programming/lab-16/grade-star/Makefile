.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LDLIBS  := -lpthread

BINS := din_phil din_phil_fixed

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(BINS)
