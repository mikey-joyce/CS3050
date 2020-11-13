/*CS 3050 Machine Problem 3 Built By:
Mikey Joyce
Sarah Duong
Tasha Ogoti*/

//libraries
#include <stdio.h>
#include <stdlib.h>

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
int insert(int *, int, int);
void maxHeapify(int *, int, int);
void heapChangeKey(int *, int, int, int);
int delete(int *, int, int);
void printHeap(int *, int);

int main(void){
  //most will consist of reading the file

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

  //!!! Test Operations !!!
  heapSize = insert(myHeap, heapSize, 7);
  //heapSize = delete(myHeap, heapSize, 0);
  //heapChangeKey(myHeap, heapSize, 3, 9);
  //heapSize = delete(myHeap, heapSize, 0);
  //heapSize = delete(myHeap, heapSize, 2);


  /*!!! This loops through the rest of the FILE
  and performs the operations as needed due to the
  switch case statement. !!!*/
  /*//loop through the remaining lines
  while(!feof(fPtr)){
    char temp;
    int i, v;
    fscanf(fPtr, "%c", &temp);

    switch(temp){
      case "I":
        //if the character is I then read in the key
        fscanf(" %d\n", &v);
        //insert new key v
        insert(myHeap, heapSize, v);
        break;
      case "C":
        //if the character is C then read in the index and key
        fscanf(" %d %d\n", &i, &v);
        //change the key of the heap at index i to a new key
        heapChangeKey(myHeap, heapSize, i, v);
        break;
      case "D":
        //if the character is D then read in the index
        fscanf(" %d\n", &i);
        //delete key at index i in the heap
        heapSize = delete(myHeap, heapSize, i);
        break;
      case default:
        fscanf("\n");
        //heapSize = delete(myHeap, heapSize, 0);
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
  //printf("\nThe Left Child of %d is: %d\n", index, LCHILD(index));

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

/**/
int delete(int *myHeap, int size, int target){

  return size;
}
