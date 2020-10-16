/*CS 3050 Machine Problem 2 Built by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

//Represents an adjacency list node
typedef struct adjlistnodestruct{
  int destination;
  struct adjlistnodestruct *next;
}AdjListNode;

//Represents and adjacency list
typedef struct adjliststruct{
  AdjListNode *head;
}AdjList;

//Represents a graph
typedef struct graphstruct{
  int totalVertices;
  int *visited;
  AdjList *myArray;
}Graph;

//Graph prototypes
AdjListNode *createNode(int);
Graph *createGraph(int);
int readVertices(FILE *);
void readEdges(FILE *, Graph *, Graph *);
void addEdge(Graph *,Graph *, int, int);
void printOutdegrees(Graph *);
void fillStack(Graph *, int, bool *, int *, int);
void DFS(Graph *, int, bool *);
void transposeGraph(Graph *, int, int);
void findSCC(Graph *, Graph *, int, int *, int);

//Stack Function Prototypes
int push(int *, int, int);
int pop(int);

int main(void){
  //open file
	FILE *fPtr = fopen("graph.txt", "r");

  //find total vertices
  int totalVertices=readVertices(fPtr);

  //set pointer back to beginning of file
  rewind(fPtr);

  //set the stack up
  int myStack[totalVertices];
  int stackCounter=-1;

  //Find graph data
  printf("Create graph\n");
  Graph *graphData1=createGraph(totalVertices);
  Graph *graphData2=createGraph(totalVertices);

  //read in the edges
  printf("Read edges\n");
  readEdges(fPtr, graphData1, graphData2);

  //find the SCC graph
  printf("Find scc\n");
  findSCC(graphData1, graphData2, totalVertices, myStack, stackCounter);
  printf("SCC found\n");
  //function for finding outdegrees maybe can be done within SCC
  //findOutdegrees() or printOutdegrees() (or both?)
  //findOutdegrees(graphData1);
  //printOutdegrees(graphData2);
	//readFile(fPtr);

  //close file and set pointer to NULL
	fclose(fPtr);
	fPtr = NULL;

  return 0;
}

void readEdges(FILE *fPtr, Graph *graphData1, Graph *graphData2){
  //while we are not at the end of the file
  while(!feof(fPtr))
	{
    //scan in the edge and add it into our graph
		int v1, v2;
		fscanf(fPtr, "%d %d\n", &v1, &v2);
		addEdge(graphData1, graphData2, v1, v2);
	}
}

int readVertices(FILE *fPtr){
  //track the maximum possible vertices and total vertices
  int maxVertices=0;
  int counter=0;

  //find maximum possible vertices
  while(!feof(fPtr)){
    int v1, v2;
    fscanf(fPtr, "%d %d\n", &v1, &v2);
    maxVertices+=2;
  }

  rewind(fPtr);

  //create an array of unique vertices if its of value -1 then it is not a vertex
  int uniqueVertices[maxVertices];
  memset(uniqueVertices, -1, maxVertices*sizeof(int));

  //while we are not at end of file
  while(!feof(fPtr)){
    //temp vertices and our totalVertices counter
    int vertexA, vertexB;

    //scan in vertices
    fscanf(fPtr, "%d %d\n", &vertexA, &vertexB);

    //loop through entire array
    for(int i=0; i<maxVertices; i++){
      //if vertexA isn't unique then break
      if(vertexA==uniqueVertices[i]){
        break;
      }
      //else if i has reached the end of the array
      else if(i==(maxVertices-1)){
        //add vertexA into the array at point counter
        uniqueVertices[counter]=vertexA;
        //increment counter and break
        counter++;
        break;
      }
    }
    //loop through entire array
    for(int j=0; j<maxVertices; j++){
      //if vertexB isn't unique then break
      if(vertexB==uniqueVertices[j]){
        break;
      }
      //else if j has recahed the end of the array
      else if(j==(maxVertices-1)){
        //add vertexB into the array at point counter
        uniqueVertices[counter]=vertexB;
        //increment counter and break
        counter++;
        break;
      }
    }
  }

  return counter;
}

void findSCC(Graph *graphData1, Graph *graphData2, int vertices, int *myStack, int stackCounter){
  bool visited[vertices];
  int count=1;

  for(int i=0; i<vertices; i++){
    visited[i]=false;
  }

  for(int j=0; j<vertices; j++){
    if(visited[j]==false){
      fillStack(graphData1, j, visited, myStack, stackCounter);
    }
  }

  for(int k=0; k<vertices; k++){
    visited[k]=false;
  }
  while(stackCounter!=-1){
    int targetIndex=myStack[stackCounter];
    stackCounter=pop(stackCounter);

    if(visited[targetIndex]==false){
      printf("SCC %d: \n", count++);
      DFS(graphData2, vertices, visited);
      printf("\n");
    }
  }
}

//create a new adj list node
AdjListNode *createNode(int data){
  //Declare and allocate memory to the new node
  AdjListNode * newNode = malloc(sizeof(AdjListNode));

  //check to see if malloc worked
  if(newNode){
    //initialize our data
    newNode->destination = data;
    newNode->next=NULL;
  }

  return newNode;
}

//create a graph with v amount of vertices
Graph* createGraph(int vertices){
  //declare and allocate memory to the new graph
  Graph *newGraph=malloc(sizeof(Graph));

  //if malloc failed
  if(newGraph == NULL){
    printf("Memory allocation failed at createGraph (1).\n");
    return NULL;
  }

  //set vertices to amount of vertices given and allocate memory
  newGraph->totalVertices = vertices;
  newGraph->myArray=malloc(vertices*sizeof(AdjList));

  //if malloc failed
  if(!newGraph->myArray){
    printf("Memory allocation failed at createGraph (2).\n");
    return NULL;
  }

  //traverse the list
  for(int i=0; i<=vertices; i++){
    //initialize this to NULL
    newGraph->myArray[i].head=NULL;
  }

  return newGraph;
}

void DFS(Graph *myGraph, int num, bool visited[]){
  //keep track of visited
  visited[num] = true;

  //print dfs
  printf("%d ", num);

  //set current head to be head of the targetNodes list
  AdjListNode *currentHead = myGraph->myArray[num].head;

  //while currentHead exists
  while(currentHead)
  {
    //if the current head destination doesn't exist in visited
    if (!visited[currentHead->destination])
    {
      //call DFS
      DFS(myGraph, currentHead->destination, visited);
    }
    //increment hold to next
    currentHead = currentHead->next;
  }
}

void addEdge(Graph *graphData1, Graph *graphData2, int source, int destination){
  //create a new node
  AdjListNode *newNode = createNode(destination);

  //make next to the new node to be the head of list one
  newNode->next = graphData1->myArray[source].head;

  //make the head of list two be the new node
  graphData2->myArray[source].head = newNode;

  //transpose our graph
  transposeGraph(graphData2, source, destination);
}

void fillStack(Graph *graphData, int data, bool visited[], int *myStack, int stackCounter){
  //array of visited
  visited[data] = true;

  //set n to be head of the list that belongs to the target node
  AdjListNode *currentNode = graphData->myArray[data].head;

  //while our node exists
  while(currentNode)
  {
    //if our nodes destination doesn't exist in visited
    if(!visited[currentNode->destination])
    {
      //fill the stack
      fillStack(graphData, currentNode->destination, visited, myStack, stackCounter);
    }
    //increment current node to next
    currentNode = currentNode->next;
  }
  stackCounter=push(myStack, stackCounter, data);
}

void transposeGraph(Graph * graphData, int source, int destination){
  //create new node
  AdjListNode *newNode = createNode(source);

  //set next of new node to be current head
  newNode->next = graphData->myArray[destination].head;

  //set the current head to be the new node
  graphData->myArray[destination].head = newNode;
}

void findOutdegrees(){

}

//Stack functions
int push(int *myStack, int stackCounter, int targetIndex){
  //increment to the first index
  stackCounter++;

  //store the target index in the stack
  myStack[stackCounter]=targetIndex;

  return stackCounter;
}

int pop(int stackCounter){
  //decrement our stack
  stackCounter--;

  return stackCounter;
}
