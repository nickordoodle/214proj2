CFLAGS = -Wall -g
CFLAGS2 = -g
COMPILER = gcc


all: mymalloc test0
	$(COMPILER) $(CFLAGS) mymalloc mymalloc.c 

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c

test0.o: test0.c
	$(COMPILER) $(CFLAGS2) -c test0.c

test0: mymalloc.o test0.o
	$(COMPILER) $(CFLAGS) -o test0 test0.o mymalloc.o
