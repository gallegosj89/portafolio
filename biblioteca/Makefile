# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source files
SRC_FILES = $(SRC_DIR)/biblioteca.c $(SRC_DIR)/memory_management.c

# Object files for verbose build
OBJ_FILES_VERBOSE = $(BUILD_DIR)/biblioteca_verbose.o $(BUILD_DIR)/memory_management_verbose.o

# Object files for normal build
OBJ_FILES_NORMAL = $(BUILD_DIR)/biblioteca.o $(BUILD_DIR)/memory_management.o

# Executable files
EXEC_WITH_DISPLAY = $(BUILD_DIR)/biblioteca_verbose.exe
EXEC_WITHOUT_DISPLAY = $(BUILD_DIR)/biblioteca.exe

# Map files
MAP_WITH_DISPLAY = $(BUILD_DIR)/biblioteca_verbose.map
MAP_WITHOUT_DISPLAY = $(BUILD_DIR)/biblioteca.map

# Targets
all: $(EXEC_WITH_DISPLAY) $(EXEC_WITHOUT_DISPLAY)

# Target with memory management display
$(EXEC_WITH_DISPLAY): CFLAGS += -DMEMORY_MANAGEMENT_DISPLAY=1
$(EXEC_WITH_DISPLAY): $(OBJ_FILES_VERBOSE)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES_VERBOSE) -Wl,-Map,$(MAP_WITH_DISPLAY)

# Target without memory management display
$(EXEC_WITHOUT_DISPLAY): CFLAGS += -DMEMORY_MANAGEMENT_DISPLAY=0
$(EXEC_WITHOUT_DISPLAY): $(OBJ_FILES_NORMAL)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES_NORMAL) -Wl,-Map,$(MAP_WITHOUT_DISPLAY)

# Object file compilation for verbose build
$(BUILD_DIR)/%_verbose.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DMEMORY_MANAGEMENT_DISPLAY=1 -c $< -o $@

# Object file compilation for normal build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DMEMORY_MANAGEMENT_DISPLAY=0 -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean