.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LDLIBS  := -lpthread

BINS := ex1_create ex2_join ex3_args ex4_cancel ex5_cleanup ex6_sleepsort

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(BINS)
