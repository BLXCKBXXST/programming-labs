.PHONY: all clean grade-3 grade-4 grade-5

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

BINS := alg08_factorial alg09_maxdigit alg10_reverse alg11_log2 alg12_digitsum

all: $(BINS)

grade-3: alg08_factorial
grade-4: alg08_factorial alg09_maxdigit alg10_reverse
grade-5: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINS)
