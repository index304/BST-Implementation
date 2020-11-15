CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

.PHONY: all clean

all: forests

forests: forests.o task.o bst.o 
	$(CC) $(LDFLAGS) -o $@ $^

bst.o: ./src/bst.c ./src/bst.h
	$(CC) $(CFLAGS) -c $<
	
task.o: ./src/task.c ./src/task.h ./src/bst.h
	$(CC) $(CFLAGS) -c $<

forests.o: ./src/forests.c ./src/bst.h ./src/task.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o forests
