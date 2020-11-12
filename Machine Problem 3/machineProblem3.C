/*CS 3050 Machine Problem 3 Built By:
Mikey Joyce
Sarah Duong
Tasha Ogoti*/

//libraries
#include <stdio.h>
#include <stdlib.h>

//structs
//I think we only need a node struct
typedef struct nodestruct{
  int data;
  struct nodestruct *left;
  struct nodestruct *right;
}Node;

//prototypes
/*!!! IMPORTANT !!!
MAKE SURE TO ADD COMMENTS
BEFORE EACH FUNCTION TO EXPLAIN
WHAT THE CODE DOES. IT IS FOR POINTS.*/
void buildMaxHeap(int *, int);
insert();
maxHeapify();
heapChangeKey();
delete();

int main(void){
  //most will consist of reading the file

  //open file
  FILE *fPtr = fopen("test.txt", "r");

  //get heap size since it will always be the first number
  int heapSize = 0;
  fscanf(fPtr, "%d\n", &heapSize);

  Node myHeap[heapSize];

  //loop through the nodes of the heap
  for(int i=0; i<heapSize; i++){
    fscanf(fPtr, "%d\n", &(myHeap[i].data));
  }
  while()
}

void buildMaxHeap(int *myHeap, int size){

}
