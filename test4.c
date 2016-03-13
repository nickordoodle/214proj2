#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {


	char *array[100];

	int i;

	for(i = 0; i < 99; i++){

		array[i] = malloc(i);
	}

	return 0;
}
