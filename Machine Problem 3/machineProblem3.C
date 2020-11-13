/*CS 3050 Machine Problem 3 Built By:
Mikey Joyce
Sarah Duong
Tasha Ogoti*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constant function definitions
#define LCHILD(x) (2 * x) + 1
#define RCHILD(x) (2 * x) + 2
#define PARENT(x) (x - 1) / 2

//prototypes
/*!!! IMPORTANT !!!
MAKE SURE TO ADD COMMENTS
BEFORE EACH FUNCTION TO EXPLAIN
WHAT THE CODE DOES. IT IS FOR POINTS.*/
void buildMaxHeap(int *, int);
int insert(int *, int, int);
void maxHeapify(int *, int, int);
void heapChangeKey(int *, int, int, int);
int delete(int *, int, int);
void printHeap(int *, int);

int main(void){
  //open file
  FILE *fPtr = fopen("test.txt", "r");

  //declare my heap
  int myHeap[1000];

  //get heap size since it will always be the first number
  int heapSize = 0;
  fscanf(fPtr, "%d\n", &heapSize);

  //loop through the nodes of the heap
  for(int i=0; i<heapSize; i++){
    //scan in the value
    fscanf(fPtr, "%d\n", &(myHeap[i]));
  }

  //build the heap so that we can perform remaining operations
  buildMaxHeap(myHeap, heapSize);

  printHeap(myHeap, heapSize);

  //!!! Test Operations !!!
  heapSize = insert(myHeap, heapSize, 7);
  buildMaxHeap(myHeap, heapSize);
  printHeap(myHeap, heapSize);

  heapSize = delete(myHeap, heapSize, 1-1);
  buildMaxHeap(myHeap, heapSize);
  printHeap(myHeap, heapSize);

  heapChangeKey(myHeap, heapSize, 3-1, 9);
  buildMaxHeap(myHeap, heapSize);
  printHeap(myHeap, heapSize);

  heapSize = delete(myHeap, heapSize, 1-1);
  buildMaxHeap(myHeap, heapSize);
  printHeap(myHeap, heapSize);

  heapSize = delete(myHeap, heapSize, 2-1);
  buildMaxHeap(myHeap, heapSize);


  /*!!! This loops through the rest of the FILE
  and performs the operations as needed due to the
  switch case statement. !!!*/
  //loop through the remaining lines
  /*while(!feof(fPtr)){
    char temp;
    int i, v, test=0;
    fscanf(fPtr, "%c", &temp);

    if(strcmp(&temp, "I")==0){
      test=1;
    }
    else if(strcmp(&temp, "C")==0){
      test=2;
    }
    else if(strcmp(&temp, "D")==0){
      test=3;
    }
    else{
      test=4;
    }

    switch(test){
      case 1:
        //if the character is I then read in the key
        fscanf(fPtr, " %d\n", &v);
        //insert new key v
        heapSize = insert(myHeap, heapSize, v);
        buildMaxHeap(myHeap, heapSize);
        break;
      case 2:
        //if the character is C then read in the index and key
        fscanf(fPtr, " %d %d\n", &i, &v);
        //change the key of the heap at index i to a new key
        heapChangeKey(myHeap, heapSize, i-1, v);
        buildMaxHeap(myHeap, heapSize);
        break;
      case 3:
        //if the character is D then read in the index
        fscanf(fPtr, " %d\n", &i);
        //delete key at index i in the heap
        heapSize = delete(myHeap, heapSize, i-1);
        buildMaxHeap(myHeap, heapSize);
        break;
      case 4:
        fscanf(fPtr, "\n");
        heapSize = delete(myHeap, heapSize, 0);
        buildMaxHeap(myHeap, heapSize);
        break;
    }
  }*/

  printHeap(myHeap, heapSize);

  fclose(fPtr);
  fPtr = NULL;
}

/*This function traverses the heap and prints out each node.*/
void printHeap(int *myHeap, int size){
  //traverse heap
  for(int i=0; i<size; i++){
    //print value
    printf("%d ", myHeap[i]);
  }
  printf("\n");
}

/*This function is passed an array: 'myHeap' and the size of the
heap: 'size'. This function makes sure the heap
property is satified so that a max-heap is built. */
void buildMaxHeap(int *myHeap, int size){
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
  int largest = (LCHILD(index) < size && myHeap[LCHILD(index)] > myHeap[index]) ? LCHILD(index) : index;

  //make sure the largest is actually the largest
  if(RCHILD(index) < size && myHeap[RCHILD(index)] > myHeap[largest]){
    largest = RCHILD(index);
  }

  //go down the heap
  if(largest != index){
    //swap myHeap[i] and myHeap[largest]
    int temp = myHeap[index];
    myHeap[index] = myHeap[largest];
    myHeap[largest] = temp;

    //go down again
    maxHeapify(myHeap, size, largest);
  }
}

/*This function takes in a heap, the size of the heap and
a key value. It then increases the size by one and
inserts the new node into the heap. After this we
heapify so that it satisfies the max-heap property.
At the end we return the new size.*/
int insert(int *myHeap, int size, int value){
  //increase size by one
  size++;

  //set last index to be our value
  myHeap[size-1] = value;

  //bubble up the heap
  maxHeapify(myHeap, size, size-1);

  //return the new size
  return size;
}

/*This function replaces the heap at target to the new value.
At the end it restores the max heap property by calling
maxHeapify();*/
void heapChangeKey(int *myHeap, int size, int target, int value){
  //change the target value
  myHeap[target]=value;

  //restore the max heap property
  maxHeapify(myHeap, size, target);
}

/*This function takes in a heap, the size of the heap,
and the target index that we are trying to delete. It will
then check to see if we are at the end of the array. If
we are at the end of the array then it will just delete
that node. If not then it will replace every node
to the right of it with the one directly to the right of
it. After this the new size is returned and the old
node can no longer be accessed.*/
int delete(int *myHeap, int size, int target){
  //decrease size
  size = size - 1;

  //if the target is the last node
  if(target==size){
    //delete node
    myHeap[target] = 0;
  }
  else{
    //if the target isn't the last node
    for(; target<=size; target++){
      //replace every node to the right with the one before it
      myHeap[target]=myHeap[target+1];
    }
    //delete the last node
    myHeap[size] = 0;
  }

  //return the new size
  return size;
}
