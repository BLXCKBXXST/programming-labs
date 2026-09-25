CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
TARGET  = sneakers_list
SRCS    = src/main.c src/list.c
INC     = -Iinclude

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INC) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
