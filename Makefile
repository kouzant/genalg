CC=gcc
PROGRAM=color_graph
SOURCE=color_graph.c linked_list.c
CFLAGS=-Wall -O3

all: color_graph.c linked_list.c proto.h
	$(CC) $(CFLAGS) $(SOURCE) -o $(PROGRAM)
clean:
	rm -rf $(PROGRAM)
