/*CS 3050 Machine Problem 3 Built By:
Mikey Joyce
Sarah Duong
Tasha Ogoti*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Constant function definitions
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

//prototypes
/*!!! IMPORTANT !!!
MAKE SURE TO ADD COMMENTS
BEFORE EACH FUNCTION TO EXPLAIN
WHAT THE CODE DOES. IT IS FOR POINTS.*/
void buildMaxHeap(int *, int);
void insert(int *, int);
void maxHeapify(int *, int, int);
void heapChangeKey(int *, int, int);
void delete(int *, int);

int main(void){
  //most will consist of reading the file

  //open file
  FILE *fPtr = fopen("test.txt", "r");

  //declare my heap
  int myHeap[1000];

  //get heap size since it will always be the first number
  int heapSize = 0;
  fscanf(fPtr, "%d\n", &heapSize);

  //build the heap so that we can perform remaining operations
  buildMaxHeap(myHeap, heapSize);

  //loop through the remaining lines
  while(!feof(fPtr)){
    char temp;
    int i, v;
    fscanf(fPtr, "%c", &temp);

    switch(temp){
      case "I":
        //if the character is I then read in the key
        fscanf(" %d\n", &v);
        //insert new key v
        insert(myHeap, v);
        break;
      case "C":
        //if the character is C then read in the index and key
        fscanf(" %d %d\n", &i, &v);
        //change the key of the heap at index i to a new key
        heapChangeKey(myHeap, i, v);
        break;
      case "D":
        //if the character is D then read in the index
        fscanf(" %d\n", &i);
        //delete key at index i in the heap
        delete(myHeap, i);
        break;
      case default:
        fscanf("\n");
        //extract max
        break;
    }
  }

  fclose(fPtr);
  fPtr = NULL;
}

/*This function is passed an array: 'myHeap' and the size of the
heap: 'size' This function reads through the given file size times and adds
the given data into an array. After this it makes sure the heap
property is satified so that a max-heap is built. */
void buildMaxHeap(int *myHeap, int size){
  //loop through the nodes of the heap
  for(int i=0; i<size; i++){
    //scan in the value
    fscanf(fPtr, "%d\n", &(myHeap[i]));
  }

  //make sure heap property is satisfied
  for(int i=((size-1)/2); i>=0; i--){
    maxHeapify(myHeap, size, i);
  }
}

/*This function takes an array: 'myHeap' the size of the heap: 'size'
and a current node index: 'index'. It then defines which node is the largest,
either the parent or one of the two children. After this if the children
are the largest then the nodes are swapped. It then recursively traverses
the max-heap until the max-heap property is satisfied.*/
void maxHeapify(int *myHeap, int size, int index){
  //define largest
  int largest = (LCHILD(i) < size && myHeap[LCHILD(i)] > myHeap[i]) ? LCHILD(i) : i;

  //make sure the largest is actually the largest
  if(RCHILD(i) < size && myHeap[RCHILD(i)] > myHeap[largest]){
    largest = RCHILD(i);
  }

  //go down the heap
  if(largest != i){
    //swap myHeap[i] and myHeap[largest]
    int temp = myHeap[i];
    myHeap[i] = myHeap[largest];
    myHeap[largest] = temp;

    //go down again
    maxHeapify(myHeap, size, largest);
  }
}
