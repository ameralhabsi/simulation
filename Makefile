CC=gcc
CFLAGS=-I. -O2 -Wall
DEPS = distributions.h
OBJ = distributions.o rands.o 

all:	test

test:	test.c $(OBJ)
	$(CC) $(CFLAGS) -o  $@ $^ -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o  $@ $< 


	
.PHONY: clean all

clean:
	rm -f *.o *~ core test test.exe

install:
	ar -rc -o libsimulation.a *.o
	cp rands.h /usr/local/include
	cp distributions.h /usr/local/include
	cp libsimulation.a /usr/local/lib
