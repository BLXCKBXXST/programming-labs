.PHONY: all clean run

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LDLIBS  := -lpthread

all: chat

chat: chat.c msgqueue.c msgqueue.h
	$(CC) $(CFLAGS) chat.c msgqueue.c -o chat $(LDLIBS)

run: chat
	./chat

clean:
	rm -f chat
