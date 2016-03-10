#include <stdlib.h>
#include <stdio.h>
#include "memory-detector.h"


/* to be used and implemented for outputing errors */

static MemEntry *smallMemPtr;
static MemEntry *bigMemPtr;
static int wasInit = 0;

/* QUESTION: HOW BIG DO WE MAKE MEMENTRIES, DO WE NEED TO USE MULTIPLE ENTRIES, AND CAN
   WE OVERLAP OR POINT TO OTHER MEMENTRIES IF WE NEED MORE MEMORY 

   How to store "struct" in our memory or char array, "treat char array as struct array"

   Beginning of newEntry struct is equal to size of mementry + size of data.

   If you add to pointer, you are adding the size of pointer type 
   So Mementrypointer + 1 adds the size of another mementry

   ((char*)construct + 1) + 10

   SPECIAL CODE??
   HOW TO IDENTIFY THE SAME OBJECTS?

   Combine two adjacent free blocks by readjusting pointers, dont combine if they aren't free however*/

int enoughMemory();


int doesPointerExist();

void setMemEntryValues(MemEntry *entry, unsigned int size){

	entry->prev = NULL;
	entry->next = NULL;
	entry->isFree = 1;
	entry->isMementry = SPECIALCODE;
   entry->size = size;
}

void *sliceMemEntry(unsigned int size, MemEntry *currMem){

   MemEntry *newEntry = (MemEntry *)((char*)currMem + sizeof(MemEntry) + size);
   newEntry->prev = currMem;                  
   newEntry->next = currMem->next;         
   if(currMem->next != NULL)                    
      currMem->next->prev = newEntry;               
   currMem->next = newEntry;                 
   newEntry->size = currMem->size - sizeof(MemEntry) - size;  
   newEntry->isFree = 1;                   
   currMem->size = size;            
   currMem->isFree = 0; 

   return newEntry;

}

/* CONDITIONS TO CHECK FOR: NO SPACE, FREE SPACE BUT NOT ENOUGH ROOM */
void *insertMemEntry(unsigned int size, MemEntry *blockPtr, char *file, int line){

   MemEntry *currMem = blockPtr;

   do{
      
      /* Make sure there is enough room for new memory allocation */
      if ( currMem->isFree && currMem->size >= (size + sizeof(MemEntry))){

         /* Adjust/Cut memEntries to insert the new allocation */
         printf("Successful malloc of size %d on line %d in file %s", size , line, file);
         return sliceMemEntry(size, currMem);

      } else{

         /* Move currMement MemEntry to the next entry */
         currMem = currMem->next;

      }
      

   } while(currMem != NULL);

   printf("UNSUCCESSFUL malloc of size %d on line %d in file %s", size , line, file);

   return NULL;
}

void initGlobals(){

   /* Set up the pointer to smaller memory allocations */
   smallMemPtr = (MemEntry *)memoryBlock;
   smallMemPtr->prev = NULL;
   smallMemPtr->next = NULL;
   smallMemPtr->size = 2499;
   smallMemPtr->isFree = 1;

   /* Set up the pointer to bigger memory allocations */
   bigMemPtr = (MemEntry *)(memoryBlock + 2499 + sizeof(MemEntry));
   bigMemPtr->prev = NULL;   
   bigMemPtr->next = NULL;   
   bigMemPtr->size = 2499 - 2 * sizeof(MemEntry); 
   bigMemPtr->isFree = 1;                  

   /* Tell the program that we have already ran the program once and 
      global variables were initialized */
   wasInit = 1;        
}

/* Our own custom implementation of malloc.  Utilizes our memory which
   is a char array called "block".  We use MemEntry structs to make 
   allocating memory easier by casting char array locations to MemEntries.
   Everytime mymalloc is called, check if globals were initialized, then
   insert the memory allocation if possible based on its size. */

void * mymalloc(unsigned int size, char * file, int line){


   /* Check if program was initialized */
   if(!wasInit){
      
      /* Memory was not initialized yet, must initialize globals*/
      initGlobals();

   } 

   if(size < 50 ){

      /* Use small block */
      return insertMemEntry(size, smallMemPtr, file, line);

   } else if(size > 50 ){

      /* Use big block */
      return insertMemEntry(size, bigMemPtr, file, line);

   } 

   /* Print error if conflicts exist */
   return NULL;
}

void * myfree(void * toFree, char * file, int line){
	
	
}

int main(int argc, char const *argv[]) {

   printf("%d\n", memoryBlock[0]);

	return 0;
}
