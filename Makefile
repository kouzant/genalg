CC=gcc
BIN=bin
PROGRAM=$(BIN)/color_graph
SRC_DIR=src
SOURCE=$(SRC_DIR)/*.c
CFLAGS=-Wall -O3

all: $(SRC_DIR)/color_graph.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/proto.h
	$(CC) $(CFLAGS) $(SOURCE) -o $(PROGRAM)
clean:
	rm -rf $(PROGRAM)
