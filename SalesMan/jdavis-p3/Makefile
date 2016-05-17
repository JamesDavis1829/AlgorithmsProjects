CFLAGS = -g -Wall 
CC = gcc

objects = main.o Map.o bruteSales.o

salesMan: $(objects)
	$(CC) -o salesMan $(objects) -lm
main.o: main.c Map.h bruteSales.h
Map.o: Map.c bruteSales.h
bruteSales.o: bruteSales.c Map.h

.PHONY : clean
clean: 
	rm $(objects) salesMan
