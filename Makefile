CC=gcc
CFLAGS=-I. -O2 -Wall
DEPS = distributions.h
OBJ = distributions.o rands.o 

all:	test

test:	test.c $(OBJ)
	$(CC) $(CFLAGS) -o  $@ $^ 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o  $@ $< 


	
.PHONY: clean all

clean:
	rm -f *.o *~ core test test.exe