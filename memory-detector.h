#include <stdlib.h>
#include <stdio.h>


#define malloc( x ) mymalloc( x, __FILE__, __LINE__ );
#define free( x ) myfree( x, __FILE__, __LINE__ );
/* DO I MALLOC THIS OR USE STACK */
/* First half of memory will be dedicated to small data portions
   for a number TBD such as (< 25, etc.) and the second half on 
   the block (2500-5000) will be dedicated to bigger data portions
   which is TBD or (> 25) */
static char memoryBlock[5000];


/* Lecture notes about project:
Have a mementry struct with fields such as sizeofallocation, next, special code, free which
points to any other pointed memory?

Account for freeing pointers to memory, preserve linked list

*/

/* Will this be useful? */
typedef struct MemEntry	MemEntry;
struct MemEntry
{

	MemEntry *next;
	MemEntry *prev;
	unsigned int size;
	int isFree;
};

void initMemEntry(MemEntry *entry);

void initGlobals();

void * mymalloc(unsigned int size, char *file, int line);

void *sliceMemEntry(unsigned int size, MemEntry *currMem);

void *insertMemEntry(unsigned int size, MemEntry *blockPtr, char *file, int line);

void myfree(void * p, char * file, int line);
