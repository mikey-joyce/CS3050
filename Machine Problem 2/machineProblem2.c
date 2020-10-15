/*CS 3050 Machine Problem 2 Built by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//Represents an adjacency list node
typedef struct adjlistnodestruct{
  int destination;
  struct adjlistnodestruct *next;
}AdjListNode;

//Represents and adjacency list
typedef struct adjliststruct{
  AdjListNode *head;
}AdjList;

/*Basic Linked list
Used as a list that each node contains a separate adj list*/
typedef struct liststruct{
  int indegree; //the idea of this is to keep track of indegree
  int outdegree; //the idea of this is to keep track of outdegree
	AdjList *myAdjList;
	struct liststruct *next;
}List;

//Represents a graph
typedef struct graphstruct{
  int totalVertices;
  int *visited;
  List *myList;
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
List *findTargetNode(Graph *, int);
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
  Graph *graphData1=createGraph(totalVertices);
  Graph *graphData2=createGraph(totalVertices);

  //read in the edges
  readEdges(fPtr, graphData1, graphData2);

  //find the SCC graph
  findSCC(graphData1, graphData2, totalVertices, myStack, stackCounter);

  //function for finding outdegrees maybe can be done within SCC
  //findOutdegrees() or printOutdegrees() (or both?)
  findOutdegrees(graphData1);
  printOutdegrees(graphData2);
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
  int totalVertices=0;

  //find maximum possible vertices
  while(!feof(fPtr)){
    maxVertices+=2;
  }

  rewind(fPtr);

  //create an array of unique vertices if its of value -1 then it is not a vertex
  int uniqueVertices[maxVertices]={-1};

  //while we are not at end of file
  while(!feof(fPtr)){
    //temp vertices and our totalVertices counter
    int vertexA, vertexB;
    counter=0;

    //scan in vertices
    fscanf(fPtr, "%d %d\n", &vertexA, vertexB);

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
      else if(i==(maxVertices-1)){
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

List *findTargetNode(Graph *graph, int target){
  //Initialize our current node and create counter
  List *currentNode;
  currentNode = graph->myList;
  int count=0;

  //traverse the list until we hit target node
  while(count!=target){
    //increment to next until target node is found
    currentNode=currentNode->next;
  }

  //return target node
  return currentNode;
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
  newGraph->myList=malloc(sizeof(List));

  //alias to simplify
  List *alias = newGraph->myList;

  //if malloc failed
  if(!alias){
    printf("Memory allocation failed at createGraph (2).\n");
    return NULL;
  }

  //initialize our data
  alias->indegree = 0;
  alias->outdegree = 0;
  alias->myAdjList->head = NULL;

  //traverse the list
  for(int i=0; i<=vertices; i++){
    List *newListNode=malloc(sizeof(List));

    //if malloc failed
    if(!newListNode){
      printf("Memory allocation failed at createGraph (3).\n");
      return NULL;
    }

    //initialize our data and increment to next
    newListNode->indegree = 0;
    newListNode->outdegree = 0;
    newListNode->myAdjList->head = NULL;
    alias->next = newListNode;
    alias = newListNode;
  }

  return newGraph;
}

void DFS(Graph *myGraph, int num, bool visited[]){
  //find target node
  List *targetNode = findTargetNode(myGraph, num);

  //keep track of visited
  visited[num] = true;

  //print dfs
  printf("%d ", num);

  //set current head to be head of the targetNodes list
  AdjListNode *currentHead = targetNode->myAdjList->head;

  //while currentHead exists
  while (currentHead)
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

  //find target nodes for both lists
  List *myList1=findTargetNode(graphData1, source);
  List *myList2=findTargetNode(graphData2, source);

  //make next to the new node to be the head of list one
  newNode->next = myList1->myAdjList->head;

  //make the head of list two be the new node
  myList2->myAdjList->head = newNode;

  //transpose our graph
  transposeGraph(graphData2, source, destination);
}

void fillStack(Graph *graphData, int data, bool visited[], int *myStack, int stackCounter){
  //find target node
  List *targetNode = findTargetNode(graphData, data);
  //array of visited
  visited[data] = true;

  //set n to be head of the list that belongs to the target node
  AdjListNode *currentNode = targetNode->myAdjList->head;

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

  //Find target node
  List *list=findTargetNode(graphData, destination);

  //set next of new node to be current head
  newNode->next = list->myAdjList->head;

  //set the current head to be the new node
  list->myAdjList->head = newNode;
}

<<<<<<< Updated upstream
=======
void findOutdegrees()
{

}

>>>>>>> Stashed changes
//Changed this function to print out degree since we dont need to print graph
void printOutdegrees(Graph *mySCC){
  printf("The outdegrees are: ");
  int count=0;
  int limit = mySCC->myList->outdegree;
  while(count!=limit)
  {
    int data = mySCC->myList->myAdjList->head->destination;
    count++;
    printf("%d ",data);
  }
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
