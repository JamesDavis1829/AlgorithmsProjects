CFLAGS = -g -Wall 
CC = gcc

objects = fifo.o heap.o queuemath.o main.o

simulation: $(objects)
	$(CC) -o test $(objects) -lm
main.o: main.c queuemath.h heap.h fifo.h
fifo.o: fifo.c heap.h
queuemath.o: queuemath.c
heap.o: heap.c queuemath.h

.PHONY : clean
clean: 
	rm $(objects)
