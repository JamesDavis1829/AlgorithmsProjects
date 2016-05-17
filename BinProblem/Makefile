CFLAGS = -g -Wall 
CC = gcc

objects = main.o bins.o fifo.o online.o offline.o

binPacker: $(objects)
	$(CC) -o binPacker $(objects) -lm
main.o: main.c fifo.h online.h offline.h bins.h
fifo.o: fifo.c 
bins.o: bins.c fifo.h
online.o: online.c bins.h fifo.h
offline.o: offline.c bins.h fifo.h

.PHONY : clean
clean: 
	rm $(objects) binPacker
