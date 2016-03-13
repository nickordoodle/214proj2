#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {


	int *ptr = malloc(200);
	free(ptr);

	return 0;
}
