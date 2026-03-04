# --- Settings ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Isrc  # -Isrc lets tests include "sha1.h"

# --- Directories ---
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# --- Files ---
# Production source files (everything in src/ except main.c)
LIB_SRCS = $(SRC_DIR)/sha1.c $(SRC_DIR)/file_io.c
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))

# --- Targets ---

# 1. The Main Tool
# It needs the Library Objects + main.o
$(BUILD_DIR)/my_sha1: $(OBJ_DIR)/main.o $(LIB_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build complete: $@"

# 2. The Test Runner
# It needs the Library Objects + test_sha1.o
$(BUILD_DIR)/tests: $(OBJ_DIR)/test_sha1.o $(LIB_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Test runner built: $@"

# --- Compilation Rules ---

# How to build .o files from src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# How to build .o files from tests/
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Helper Commands ---

.PHONY: clean run_tests check

clean:
	rm -rf $(BUILD_DIR)

# Run the test suite
run_tests: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests

check: $(BUILD_DIR)/my_sha1
	@echo "Checking hello.txt..."
	@diff \
		<(./$(BUILD_DIR)/my_sha1 tests/inputs/hello.txt | awk '{print $$1}') \
		<(sha1sum tests/inputs/hello.txt | awk '{print $$1}') \
		&& echo "PASS: hello.txt" || echo "FAIL: hello.txt"
	@diff \
		<(./$(BUILD_DIR)/my_sha1 tests/inputs/abc.txt | awk '{print $$1}') \
		<(sha1sum tests/inputs/abc.txt | awk '{print $$1}') \
		&& echo "PASS: abc.txt" || echo "FAIL: abc.txt"
