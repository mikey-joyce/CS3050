/*CS 3050 Machine Problem 3 Built By:
Mikey Joyce
Sarah Duong
Tasha Ogoti*/

//libraries
#include <stdio.h>

//Constant function definitions
#define L_CHILD(index) (2 * index) + 1
#define R_CHILD(index) (2 * index) + 2

//prototypes
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

  /*!!! This loops through the rest of the FILE
  and performs the operations as needed due to the
  switch case statement. !!!*/
  //loop through the remaining lines
  while(!feof(fPtr)){
    //declare temporary character holder
    char temp;

    //declare my index, value, and test variables
    int i, v;

    //scan in the letter
    fscanf(fPtr, "%c", &temp);

    //if it is of type I, C, D, or E
    switch(temp){
      case 'I':
        //if the character is I then read in the key
        fscanf(fPtr, " %d\n", &v);
        //insert new key v
        heapSize = insert(myHeap, heapSize, v);
        break;
      case 'C':
        //if the character is C then read in the index and key
        fscanf(fPtr, " %d %d\n", &i, &v);
        //change the key of the heap at index i to a new key
        heapChangeKey(myHeap, heapSize, i-1, v);
        break;
      case 'D':
        //if the character is D then read in the index
        fscanf(fPtr, " %d\n", &i);
        //delete key at index i in the heap
        heapSize = delete(myHeap, heapSize, i-1);
        break;
      default:
        //if the character is E then read in the newline
        fscanf(fPtr, "\n");
        //delete the root
        heapSize = delete(myHeap, heapSize, 0);
        break;
    }
  }

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
  int largestNode = (L_CHILD(index) < size && myHeap[L_CHILD(index)] > myHeap[index]) ? L_CHILD(index) : index;

  //make sure the largest is actually the largest
  if(R_CHILD(index) < size && myHeap[R_CHILD(index)] > myHeap[largestNode]){
    largestNode = R_CHILD(index);
  }

  //go down the heap
  if(largestNode != index){
    //swap myHeap[i] and myHeap[largest]
    int temp = myHeap[index];
    myHeap[index] = myHeap[largestNode];
    myHeap[largestNode] = temp;

    //go down again
    maxHeapify(myHeap, size, largestNode);
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

  //build heap again
  buildMaxHeap(myHeap, size);

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

  //build heap again
  buildMaxHeap(myHeap, size);
}

/*This function takes in a heap, the size of the heap,
and a target node to delete. After this it decrements
the size since we are deleting a node. It checks to see
if the target is already the root, if the target is
the root it replaces the root and heapifies. If the
target is not the root, the target and root are switched
and then it replaces the root and heapifies. The new
size is returned at the end.*/
int delete(int *myHeap, int size, int target){
  //decrement size because we need one less node
  size--;

  //if the target is the root
  if(target==0){
    //replace and heapify
    myHeap[0]=myHeap[size];
    maxHeapify(myHeap, size, 0);
  }
  //if target is not the root
  else{
    //swap target and the root
    int temp=myHeap[0];
    myHeap[0]=myHeap[target];
    myHeap[target]=temp;

    //replace and heapify
    myHeap[0]=myHeap[size];
    maxHeapify(myHeap, size, 0);
  }

  //build heap again
  buildMaxHeap(myHeap, size);
  
  //return the new size
  return size;
}
