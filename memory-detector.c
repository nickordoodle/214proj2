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

   Beginning of next struct is equal to size of mementry + size of data.

   If you add to pointer, you are adding the size of pointer type 
   So Mementrypointer + 1 adds the size of another mementry

   ((char*)construct + 1) + 10

   Combine two adjacent free blocks by readjusting pointers, dont combine if they aren't free however*/

int enoughMemory();


int doesPointerExist();

void setMemEntryValues(MemEntry *entry, unsigned int size){

	entry->prev = NULL;
	entry->next = NULL;
	entry->isFree = 1;
   entry->size = size;
}

/* CONDITIONS TO CHECK FOR: NO SPACE, FREE SPACE BUT NOT ENOUGH ROOM */
int insertMemEntry(MemEntry *newEntry, MemEntry *blockPtr){

   MemEntry *curr = blockPtr;
   MemEntry *next = curr->next;

   while(curr != NULL){

      /* Make sure there is enough room for new memory allocation */
      if ( curr->isFree && curr->size >= (newEntry->size + sizeof(MemEntry))){

         next = (MemEntry *)((char*)curr + sizeof(MemEntry) + newEntry->size);
         next->prev = curr;                  
         next->next = curr->next;         
         if(curr->next != NULL)                    
            curr->next->prev = next;               
         curr->next = next;                 
         curr->size = curr->size - sizeof(MemEntry) - newEntry->size;  
         curr->isFree = 1;                   
         curr->size = newEntry->size;            
         curr->isFree = 0; 
         return 1;
      }
      
      /* Move current MemEntry to the next free space */
      curr = next;

   }

     //return (char*)p + sizeof(MemEntry);    //returns the allocated chunk, but not the header of the allocated chunk.


   return 0;
}

void * mymalloc(unsigned int size, char * file, int line){

   /* Check if program was initialized */
   if(wasInit){

      /* Execute normal code */
      MemEntry *newEntry = {0};
      setMemEntryValues(newEntry, size);

      if(size < 50 ){

         /* Use small blocksck */
         insertMemEntry(newEntry, smallMemPtr);

      } else if(size > 50 ){

         /* Use big block */
         insertMemEntry(newEntry, bigMemPtr);

      } else{

         /* Failure, print error */

      }

   } else{

      /* Memory was not initialized yet, must initialize globals*/

      /* Set up the pointer to smaller memory allocations */
      smallMemPtr = (MemEntry *)memoryBlock;
      smallMemPtr->prev = NULL;
      smallMemPtr->next = NULL;
      smallMemPtr->size = 2500;
      smallMemPtr->isFree = 1;

      /* Set up the pointer to bigger memory allocations */
      bigMemPtr = (MemEntry *)(memoryBlock + 2500 + sizeof(MemEntry));
      bigMemPtr->prev = NULL;   
      bigMemPtr->next = NULL;   
      bigMemPtr->size = 2500 - 2 * sizeof(MemEntry); 
      bigMemPtr->isFree = 1;                  

      /* Tell the program that we have already ran the program once and 
         global variables were initialized */
      wasInit = 1;              

   }

   /* Print error if conflicts exist */
   return NULL;
}



int main(int argc, char const *argv[]) {

   printf("%d\n", memoryBlock[0]);

	return 0;
}