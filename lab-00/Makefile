.PHONY: all clean task0 task1 task2 task3 task4

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LDLIBS  :=

all: task0 task1 task2 task3 task4

task0: task0/hello
task1: task1/output
task2: task2/overflow
task3: task3/chars
task4: task4/after

task0/hello:    task0/hello.c    ; $(CC) $(CFLAGS) $< -o $@
task1/output:   task1/output.c   ; $(CC) $(CFLAGS) $< -o $@
task2/overflow: task2/overflow.c ; $(CC) $(CFLAGS) $< -o $@
task3/chars:    task3/chars.c    ; $(CC) $(CFLAGS) $< -o $@
task4/after:    task4/after.c    ; $(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -f task0/hello task1/output task2/overflow task3/chars task4/after
