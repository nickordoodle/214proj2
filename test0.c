#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

	int *ptr = malloc(sizeof(int));
	free(ptr);


	return 0;
}
