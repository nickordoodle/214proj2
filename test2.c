#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

	int *ptr = malloc(20);

	int *ptr2 = malloc(25);

	free(ptr);

	int *ptr3 = malloc(55);
	int *ptr4 = malloc(100);

	free(ptr3);
	free(ptr4);

	return 0;
}
