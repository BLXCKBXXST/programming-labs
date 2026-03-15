CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
AR      = ar
ARFLAGS = rcs

SRC_DIR     = src
INC_DIR     = include
BUILD_DIR   = build

SRCS        = $(SRC_DIR)/sneakers.c
OBJS        = $(BUILD_DIR)/sneakers.o
LIB         = $(BUILD_DIR)/libsorting.a
MAIN_OBJ    = $(BUILD_DIR)/main.o
TARGET      = sneakers

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/sneakers.o: $(SRC_DIR)/sneakers.c $(INC_DIR)/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(BUILD_DIR)/sneakers.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/sneakers.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD_DIR)/main.o $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
