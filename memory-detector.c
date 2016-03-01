#include <stdlib.h>
#include <stdio.h>
#include "memory-detector.h"


/* to be used and implemented for outputing errors */
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ );
#define free( x ) myfree( x, __FILE__, __LINE__ );


/* QUESTION: HOW BIG DO WE MAKE MEMENTRIES, DO WE NEED TO USE MULTIPLE ENTRIES, AND CAN
   WE OVERLAP OR POINT TO OTHER MEMENTRIES IF WE NEED MORE MEMORY */

int enoughMemory();


int doesPointerExist();

void initMemEntry(MemEntry *entry){

	entry->prev = NULL;
	entry->next = NULL;
	entry->isFree = 1;
}


int main(int argc, char const *argv[]) {


	return 0;
}