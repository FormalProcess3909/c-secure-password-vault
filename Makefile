# Build settings
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -std=c11 -Iinclude
LDFLAGS :=

# Project files
TARGET  := vault
SRC     := src/main.c src/vault.c

.PHONY: all clean run help init

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

help: $(TARGET)
	./$(TARGET) help

init: $(TARGET)
	./$(TARGET) init

clean:
	rm -f $(TARGET)