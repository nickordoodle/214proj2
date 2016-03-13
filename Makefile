COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: mymalloc test0 test1 test2 test3 test4
.PHONY: all
.PHONY: clean


mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c

mymalloc: mymalloc.o 
	$(COMPILER) $(CFLAGS) -o mymalloc mymalloc.o

test0.o: test0.c
	$(COMPILER) $(CFLAGS2) -c test0.c

test0: mymalloc.o test0.o
	$(COMPILER) $(CFLAGS) -o test0 test0.o mymalloc.o

test1.o: test1.c
	$(COMPILER) $(CFLAGS2) -c test1.c

test1: mymalloc.o test1.o
	$(COMPILER) $(CFLAGS) -o test1 test1.o mymalloc.o

test2.o: test2.c
	$(COMPILER) $(CFLAGS2) -c test2.c

test2: mymalloc.o test2.o
	$(COMPILER) $(CFLAGS) -o test2 test2.o mymalloc.o

test3.o: test3.c
	$(COMPILER) $(CFLAGS2) -c test3.c

test3: mymalloc.o test3.o
	$(COMPILER) $(CFLAGS) -o test3 test3.o mymalloc.o

test4.o: test4.c
	$(COMPILER) $(CFLAGS2) -c test4.c

test4: mymalloc.o test4.o
	$(COMPILER) $(CFLAGS) -o test4 test4.o mymalloc.o

clean: 
	rm -f *.o mymalloc test0 test1 test2 test3 test4