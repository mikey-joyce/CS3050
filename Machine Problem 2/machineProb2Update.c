#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//Represents an adjacency list node
typedef struct adjlistnodestruct{
  int destination;
  struct adjlistnodestruct *next;
}AdjListnode;

//Represents and adjacency list
typedef struct adjliststruct{
  AdjListNode *head;
}AdjList;

/*Basic Linked list
Used as a list that each node contains a separate adj list*/
typedef struct liststruct{
  int indegree; //the idea of this is to keep track of indegree
  int outdegree; //the idea of this is to keep track of outdegree
  /*for the indegree and outdegree if we keep track of this then
  we may just set it to 0 and create a separate function to tell
  where it is going*/
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
void readFile(FILE *);
void addEdge(Graph *,Graph *, int, int);
void printGraph(Graph *);
void fillStack(Graph *graphData, int v, bool checked[], int *stack);
void DFS(Graph * myGraph, int num, bool visit[]);
void transposeGraph(Graph *, int, int);

//Stack Function Prototypes
//changed to void and should still make sense
void *push(AdjListNode *, int);
void *pop(AdjListNode *);

//new prototype
List *findTargetNode(Graph *, int);

int main(void)
{
	FILE *fPtr = fopen("graph.txt", "r");
	readFile(fPtr);
	fclose(fPtr);
	fPtr = NULL;
}

/*AS OF NOW THIS IS WRONG
FIRST WE READ IN THE AMOUNT OF VERTICES
THEN WE ADD THE EDGES*/
void readFile(FILE *fPtr)
{
  int numOfLines = 0, next, destination;
  int line = 1;
  int length = 0;

   //Loops through the file to find the largest vertex
   while(!feof(fPtr))
   {
	    int startV,endV;

	    fscanf(fPtr, "%d %d\n", &startV, &endV);
	    if(startV >= endV && startV > length)
	    {
	      length = startV;
	    }
	    else if(endV >= startV && endV > length)
	    {
	       length = endV;
      }
   }
   //printf("The size of the graph should be %d\n",length);

  //Sets the pointer back to the beginning of the file
  rewind(fPtr);

	while(fscanf(fPtr, "%d %d", &next, &destination) == 2){
		numOfLines++;

    printf("%d: Next: %d, Destination: %d\n", line, next, destination);
    line++;
	}
}

List *findTargetNode(Graph *graph, int target){
  //Initialize our current node and create counter
  List currentNode=graph->myList;
  int count=0;

  //traverse the list until we hit target node
  while(count!=target){
    //increment to next until target node is found
    currentNode=currentNode->next;
  }

  //return target node
  return currentNode;
}

//create a new adj list node
AdjListNode* createNode(int data){
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
Graph* createGraph(int v){
  //declare and allocate memory to the new graph
  Graph *newGraph=malloc(sizeof(Graph));
  List *alias;

  //if malloc failed
  if(newGraph == NULL){
    printf("Memory allocation failed at createGraph (1).\n");
    return NULL;
  }

  //set vertices to amount of vertices given and allocate memory
  newGraph->totalVertices = v;
  newGraph->myList=malloc(sizeof(List));

  //alias to simplify
  alias = newGraph->myList;

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
  for(int i=0; i<=v; i++){
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

void DFS(Graph * myGraph, int num, bool visit[])
{
  //find target node
  List *targetNode=findTargetNode(myGraph, num);

  //keep track of visited
  visit[num] = true;

  //print dfs
  printf("%d ", num);

  //set hold to be head of the targetNodes list
  AdjListNode *hold = targetNode->myAdjList->head;

  //while hold exists
  while (hold)
  {
    //if the hold destination doesn't exist in visited
    if (!visit[hold->destination])
    {
      //call DFS
      DFS(myGraph, hold->destination, visit);
    }
    //increment hold to next
    hold = hold->next;
  }
}

void addEdge(Graph *graphData1, Graph *graphData2, int src, int dest)
{
  //create a new node
  AdjListNode *temp=createNode(dest);

  //find target nodes for both lists
  List *myList1=findTargetNode(graphData1, src);
  List *myList2=findTargetNode(graphData2, src);

  //make next to the new node to be the head of list one
  temp->next = myList1->myAdjList->head;

  //make the head of list two be the new node
  myList2->myAdjList->head = temp;

  //transpose our graph
  transposeGraph(graphData2, src, dest);
}

void fillStack(Graph *graphData, int data, bool visit[], int *stack)
{
  //find target node
  List *targetNode=findTargetNode(graphData, data);
  //array of visited
  visit[data] = true;

  //set n to be head of the list that belongs to the target node
  AdjListNode *currentNode = targetNode->myAdjList->head;

  //while our node exists
  while(currentNode)
  {
    //if our nodes destination doesn't exist in visited
    if(!visit[currentNode->destination])
    {
      //fill the stack
      fillStack(graphData, currentNode->destination, visit, stack);
    }
    //increment current node to next
    currentNode = currentNode->next;
  }
  push(currentNode, data);
}

void transposeGraph(Graph * graphData, int src , int dest)
{
  //create new node
  AdjListNode *newNode = createNode(src);

  //Find target node
  List *list=findTargetNode(graphData, dest);

  //set next of new node to be current head
  newNode->next = list->myAdjList->head;

  //set the current head to be the new node
  list->myAdjList->head = newNode;
}

/*WE MAY NOT NEED THIS FUNCTION*/
void printGraph(Graph *outDegGraph)
{
  printf("The outdegrees are: ");
  for(int i = 0; i <= outDegGraph->totalVertices; i++){
    List *targetNode=findTargetNode(outDegGraph, i);
    AdjListnode *hold = targetNode->myAdjList->head;
    while(hold)
    {
      //printf("%d  ",outdegree);
      printf("%d\n", hold->destination);
      hold = hold->next;
      i+=1;
    }
  }
}

//Stack functions
void *push(AdjListNode *myNode, int data){
  //Create new node
	AdjListNode *newNode = createNode(data);

  //set new node to be the head of the list
	newNode->next=myNode;

  //changed to void because it should still be doing the arithmetic?
  //return the new head
	//return newNode;
}

void *pop(AdjListNode *myNode){
  //create temp node and set it to be the next of current head node
	AdjListNode *temp = myNode->next;

  //delete the current head node
	myNode->destination = 0;
	myNode->next = NULL;
	free(node);

  //changed to void because it should still be doing the arithmetic?
  //return the new head
	//return temp;
}
