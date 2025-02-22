CC=gcc
CFLAGS=-I. -O2 -Wall -Wextra -Wpedantic
DEPS = distributions.h
OBJ = distributions.o rands.o

all:	test libsimulation.a

test:	test.c $(OBJ)
	$(CC) $(CFLAGS) -o  $@ $^ -lm

libsimulation.a:	$(OBJ)
#	$(CC) -c $(CFLAGS) $(OBJ)
	ar rcs $@ $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o  $@ $<



.PHONY: clean all

clean:
	rm -f *.o *~ core test test.exe a.exe a.out libsimulation.a

install:
	ar -rc -o libsimulation.a *.o
	cp rands.h /usr/local/include
	cp distributions.h /usr/local/include
	cp libsimulation.a /usr/local/lib
