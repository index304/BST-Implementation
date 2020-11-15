CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

.PHONY: all clean

all: forests

forests: forests.o task.o bst.o 
	$(CC) $(LDFLAGS) -o $@ $^

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c $<
	
task.o: task.c task.h bst.h
	$(CC) $(CFLAGS) -c $<

forests.o: forests.c bst.h task.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o forests
