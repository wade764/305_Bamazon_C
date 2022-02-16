# makes bamazon
# % make
# % make bamazon
# % make clean
CC = gcc
CFLAGS = -g -Wall

default: bamazon

bamazon: main.c bamazon.c bamazon.h
	@echo 'building bamazon.'
	$(CC) $(CFLAGS) -o bamazon main.c bamazon.c

clean:
	rm -f bamazon *.o
