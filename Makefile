CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g -Iinclude -MMD -MP
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = bin/app

# Tools
CLANG_FORMAT = clang-format
CLANG_TIDY = clang-tidy

all: $(TARGET)

$(TARGET): $(OBJ) | bin
	@echo "Linking $@"
	@$(CC) $(OBJ) -o $@

build/%.o: src/%.c | build
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

bin build:
	mkdir -p $@

clean:
	@rm -rf bin build

run: all
	@./$(TARGET)

format:
	@echo "Formatting code..."
	@$(CLANG_FORMAT) -i src/*.c include/*.h

lint:
	@echo "Running static analysis..."
	@$(CLANG_TIDY) src/*.c -- -Iinclude

check: format lint all

.PHONY: all clean run format lint check
