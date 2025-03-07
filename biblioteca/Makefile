CC=gcc
CFLAGS=-I. -Xlinker -Map=output.map
BIN_DIR=dist
SRC_DIR=src

biblioteca:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/biblioteca.exe $(SRC_DIR)/biblioteca.c

test:
	$(CC) -o $(BIN_DIR)/test.exe $(SRC_DIR)/test.c
