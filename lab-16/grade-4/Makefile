.PHONY: all clean benchmark

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2
LDLIBS  := -lpthread

BINS := ex7_sync ex8_matmul ex9_benchmark

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

benchmark: ex9_benchmark
	python3 benchmark.py

clean:
	rm -f $(BINS) benchmark.csv benchmark.png
