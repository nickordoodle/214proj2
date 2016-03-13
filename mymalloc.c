#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"


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
	entry->isMemEntry = SPECIALCODE;
  entry->size = size;
}

void *sliceMemEntry(unsigned int size, MemEntry *currMem){
	void * ptr = NULL;
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
   currMem->isMemEntry = SPECIALCODE;
   ptr = (void*)(newEntry+1);

   return ptr;

}

/* CONDITIONS TO CHECK FOR: NO SPACE, FREE SPACE BUT NOT ENOUGH ROOM */
void *insertMemEntry(unsigned int size, MemEntry *blockPtr, char *file, int line){

   MemEntry *currMem = blockPtr;

   do{
      
      /* Make sure there is enough room for new memory allocation */
      if ( currMem->isFree && currMem->size >= (size + sizeof(MemEntry))){

         /* Adjust/Cut memEntries to insert the new allocation */
         printf("Successful malloc of size %d on line %d in file %s \n", size , line, file);
         return sliceMemEntry(size, currMem);

      } else{

         /* Move currMement MemEntry to the next entry */
         currMem = currMem->next;

      }
      

   } while(currMem != NULL);

   printf("UNSUCCESSFUL malloc of size %d on line %d in file %s \n", size , line, file);

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
   bigMemPtr->size = 2499 - (2 * sizeof(MemEntry)); 
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

    void *result = 0;
   /* Check if program was initialized */
   if(!wasInit){
      
      /* Memory was not initialized yet, must initialize globals*/
      initGlobals();

   } 

   if(size < 50 ){

      /* Use small block */
    result = insertMemEntry(size, smallMemPtr, file, line);
    if(result != NULL)
      return result;

   } else if(size > 50 ){

      /* Use big block */
    result = insertMemEntry(size, bigMemPtr, file, line);
    if(result != NULL)
      return result;

   } 

   /* Print error if conflicts exist */
   printf("UNSUCCESSFUL malloc of size %d on line %d in file %s.  Not enough memory. \n", size , line, file);
   return NULL;
}

void* isPointer(void * toFree){
        MemEntry * toCheck = (MemEntry*)toFree;
        toCheck = toCheck - 1;
        if(toCheck -> isMemEntry == SPECIALCODE)
                return toCheck;

        return NULL;
}


void checkForAdjFreed(MemEntry * toCheck){
        int toAdd;
        /*dealing with prev*/
        if(toCheck-> prev != NULL){
                if( (toCheck -> prev -> isFree) == 1){
                        toAdd = toCheck->size + sizeof(MemEntry);
                        toCheck = toCheck -> prev;
                        toCheck -> size += toAdd;

                        toCheck -> next = toCheck -> next -> next;
                        if(toCheck -> next != NULL)
                                toCheck-> next -> prev = toCheck;
                }
        }

        if(toCheck-> next != NULL){
                if( (toCheck -> next -> isFree) == 1){
                        toAdd = toCheck->next->size  + sizeof(MemEntry);
                        toCheck -> size += toAdd;

                        toCheck -> next = toCheck -> next -> next;
                        if(toCheck -> next != NULL)
                                toCheck-> next -> prev = toCheck;
                }
        }
}


int  myfree(void * toFree, char * file, int line){
        MemEntry * ptrToFree = NULL;

        /*out of range check*/
if((char*)toFree - sizeof(MemEntry) <= (char*)smallMemPtr && (char*)toFree >= (char*)smallMemPtr + 5000 - sizeof(MemEntry))
                return 0;

        ptrToFree = isPointer(toFree);
        if(ptrToFree  == NULL);
                return 0;


        ptrToFree = (MemEntry *)toFree;
	
	ptrToFree->isFree = 1;
	
        checkForAdjFreed(ptrToFree);
        
        return 1;

}

int testLL(){
        int count = 0;
        MemEntry * currEntry = smallMemPtr;
        while(currEntry->next != NULL){
                printf("MemEntry %d space:%d free:%d\n",count,currEntry->size,currEntry->isFree);
                currEntry = currEntry->next;
                count++;
        }
        printf("End of memory\n");
        return 0;
}
/*
int main(int argc, char const *argv[]) {
   int i = 0;

   int *ptr = malloc(2400);
   int *ptr2 = malloc(2600);
   free(ptr);
    char * testArray [50];
        for(i = 0;i < sizeof(testArray)/sizeof(testArray[0]);i++)
                testArray[i] = NULL;

        i = 0;
        testArray[i] = (char*)malloc(18);
        testArray[i]= "12345678901234567";
        while(testArray[i] != NULL){
                i++;
                testArray[i] =(char*)malloc(18);
                if(testArray[i] !=NULL){
                        testArray[i]= "12345678901234567";
                }
        }
        printf("\n");
        testLL();

        for(i = 0;i < sizeof(testArray)/sizeof(testArray[0]);i++)
                printf("Mem number %d: %s\n",i,testArray[i]);

        free(testArray[0]);

        testArray[i] = malloc(18);
	testArray[i]= "12345678901234567";

   printf("%d\n", memoryBlock[0]);

	return 0;
} */
