/*Created by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include <stdio.h>
#include <stdlib.h>

//linked list structs
typedef struct Node{
  int data;
  struct Node *next;
}Node;

typedef struct List{
  int total;
  struct Node *head;
}List;

//graph structs
typedef struct Edge{
  struct Vertex *vertex;
}Edge;

typedef struct Vertex{
  int data;
  struct List *edges;
}Vertex;

typedef struct Graph{
  struct List *vertices;
}Graph;

//Prototypes for linked list
//!!!!!! DEVELOP THESE FIRST !!!!!!!!!
//readFile(); //might be a double pointer of type Node but unsure of this. Also this file will be big bc we should be converting to an adjList here.
List initList();
Node createNode(int);//create a node in our linked list
int enQueue(List*, int);//use a queue for the list
Node *deQueue(List*);
void printList(List*);//prints it out in the correct order
void freeList(List*);//frees our memory

//Prototypes for graph
Graph *initGraph();
Vertex *createVertex(int);
Edge *createEdge(Vertex*);
int compareEdges(Edge*, Edge*);
void addVertex(Graph*, Vertex*);
void removeVertex(Graph*, Vertex*);
void addEdge(Vertex*, Edge*);
void removeEdge(Vertex*, Edge*);
void addEdge_toVertex(Vertex*, Vertex*);
void freeGraph(Graph*);
void freeVertex(Vertex*);
//maybe 2 more functions to sort vertices and edges? we will see if we need it later

//Linked List functions

List initList(){
	//Declare and allocate memory to myList
	List *myList = malloc(sizeof(List));

	//check to see if malloc worked
	if(myList==NULL){
		//Malloc failed so return NULL
		return NULL;
	}

	//initialize the head of the list to NULL and total to 0
	myList->head = NULL;
	myList->total = 0;

	return myList;
}

void readFile(FILE * fPtr)
{
	/*In the case that the name of the file is not pre-determined 
	
	void readFile(const char *TheFile)
	{
		FILE *fPtr=fopen(TheFile,"r");
	
	
	*/
	int vertexA; // first number in line
	int vertexB; // second number in line
	/*int numLines = 1; // track total number of lines*/
	int numOfLines = 1; // track total number of lines
	int numVertices = 1; // track total number of vertices
	int count = 0;
	int numLines = 0;
	
	fPtr = fopen("graph.txt", "r"); // open file for reaeding
	
	// malloc checking
	if(fPtr == NULL)
		printf("File could not be opened or read.\n");
	
	// scan in values from file and find smallest and largest
	while(fscanf(fPtr, "%d %d", &vertexA, &vertexB) == 2)
	{
		List * myList;
		
		// insert values into 2d array
		/*myList[n][0] = vertexA;
		myList[n][1] = vertexB;*/
		myList[numOfLines][0] = vertexA;
		myList[numOfLines][1] = vertexB;
		
		int max = vertexB;
		
		// compare to find largest value
		if((vertexB > count) && (vertexA <= vertexB))
		{
			count = vertexB;
		}
		if((vertexA > count) && (vertexA >= vertexB))
		{
			count = vertexA;
		}
		count++;
		numOfLines++;
	}	
	
	// create adjList, insert values into list
	List myList[numVertices + 1][numVertices + 1] = malloc(sizeof(int) * (numVertices + 1));
	for (int j = 1; j <= numVertices; j++)
    	{
		for (int i = 0; i < numLines; i++)
		{
			int key = -1;
			
			Graph ** myGraph;
			
			if (myGraph[i][0] == j)
			{
			key = myGraph[i][1];
			}
			
			if (myGraph[i][1] == j)
			{
				key = myGraph[i][0];
			}
			
			if (key != -1)
			{
				myList[key][index[key]] = j;
				index[key] += 1;
			}
		}
	}
	fclose(fPtr); // close file
}

Node createNode(int data){
	//Declare and allocate memory to myNode
	Node *myNode = malloc(sizeof(Node));

	//check to see if malloc worked
	if(myNode==NULL){
		//Malloc failed return NULL
		return NULL;
	}

	//initialize myNode's data and next pointer
	myNode->data = data;
	myNode->next = NULL;

	return myNode;
}

int enQueue(List *myList, int data){
	//Declare and initialize the new node with the given data
	Node *newNode;
	newNode = createNode(data);

	//If valid
	if(newNode){
		//Set the new nodes next pointer to be ahead of the current head
		newNode->next = myList->head;

		//Set the new head to be the new node
		myList->head = newNode;

		//Increment the running total
		myList->total++;

		//Return the new head of the list
		return newNode;
	}
	else{
		//Node was not valid
		return NULL;
	}
}

Node *deQueue(List *myNode){
	//create temporary nodes
	Node *temp = myNode->head;
	Node *temp2;

	//traverse the list
	while(temp->next!=NULL){
		//Obtains the tail of the list
		temp2 = temp;
		temp = temp->next;
	}
	//Once node is found free memory and set its next pointer to NULL
	free(temp2->next);
	temp2->next = NULL;

	//return head of the list.
	return myNode->head;
}

void printList(List * myList)
{
	//alias to the Node pointer
	Node * myNode = myList->head;

	//traverse the list
	while(myNode!=NULL){
		//set i to data
		int i = myNode->data;

		//print the data
		printf("%d\n", i);

		//go to the next node
		myNode = myNode->next;
	}
}

void freeList(List *myList){
	//alias to the Node pointer and temp pointer
	Node *myNode = myList->head;
	Node *temp;

	//traverse list
	while(myNode!=NULL){
		//set temp to current node
		temp = myNode;

		//set current node to be the next node
		myNode = myNode->next;

		//free current node
		free(temp);
	}

	//free list
	free(myList);

	//for testing purposes
	//!!!! OMIT THIS LINE BEFORE TURNING IN !!!!!
	printf("Free was successful!\n");
}

//Graph Functions

Graph *initGraph(){
	//declare and allocate memory to myGraph
	Graph *myGraph = malloc(sizeof(Graph));

	//initialize my graph
	myGraph->vertices = initList();

	return myGraph;
}

Vertex *createVertex(int data){
	//declare and allocate memory to myVertex
	Vertex *myVertex = malloc(sizeof(Vertex));

	//check if malloc works
	if(myVertex==NULL){
		//Malloc failed return NULL
		return NULL;
	}

	//initialize our vertex
	myVertex->data = data;
	myVertex->edges = initList();

	return myVertex;
}

Edge *createEdge(Vertex *myVertex){
	//declare and allocate memory to edge
	Edge *myEdge = malloc(sizeof(Edge));

	//initialize the data
	myEdge->vertex = myVertex;

	return myEdge;
}

int compareEdges(Edge *edgeOne, Edge *edgeTwo){
	//might not need unless we do a weighted graph which I don't think we are doing
}

void addVertex(Graph *myGraph, Vertex *myVertex){
	enQueue(myGraph->vertices, myVertex);
}

void removeVertex(Graph * myGraph, Vertex * myVertex){
	deQueue(myGraph->vertices);
}

void addEdge(Vertex *myVertex, Edge *myEdge){
	enQueue(myVertex->edges, myEdge);
}

void removeEdge(Vertex * myVertex, Edge * myEdge){
	deQueue(myVertex->edges);
	
	/*will require a call to the dequeue function but we may need to change
	dequeue from a normal queue to where it can target said edge
	instead of targeting the tail of the list*/
}

void addEdge_toVertex(Vertex* OneV, Vertex* TwoV){
	if(OneV==NULL||TwoV==NULL)
	{
		printf("Either of the vertex does not exist at the function addEdge_toVertex.\n");
	}
	OneV->edges=TwoV;

}

void freeGraph(Graph *myGraph){
	//free all associated vertices
	freeList(myGraph->vertices);

	//free the graph
	free(myGraph);
}

void freeVertex(Vertex *myVertex){
	//free associated list
	freeList(myVertex->edges);

	//free the vertex
	free(myVertex);
}

//The code in this comment needs to be adapted to the above code
/*
struct adjList ** initList(int size)
{
  struct adjList **headNode;
  headNode = (struct adjList**)malloc(size*sizeof(struct adjList));
  if(headNode == NULL)
  {
    printf("List could not be initialized");
    free(headNode); // free allocated node
  }
  else
  {
    return headNode;
  }
}

readFile(FILE * fPtr)
{
  fscanf(fPtr, "");
	return fPtr;
}

struct adjList** createNode(struct adjList** headNode, int a, int b)
{
	return newNode;
}

addNode()
{
  createNode(struct adjList ** headNode, int a, int b);
}

int compare(struct node * prevNode, struct node * curNode)
{
	// compare node for inc size
  if(prevNode==NULL || curNode==NULL)
  {
    printf("Please input a valid Node before comparing.\n";
  }
  if((prevNode->data) == (curNode->data))
  {
    return 1;
  }
  return 0;
}

void printList(struct adjList ** headNode)
{
  if(headNode==NULL)
  {
    printf("The adjacency list is empty.\n");
    return;
  }

  //Loop through the adjacency list to print out the vertices
  for(int i=0; Node * headNode[i]->graph->next == NULL;i++)
  {
    //
    while( headNode[i]->graph->next != NULL)
    {
      headNode[i]->graph=headNode[i]->graph->next;
      int value=headNode[i]->graph->data;
      printf("%d",value);;
    }
    printf("\n");
  }
	return;
}

void freeNodes(struct adjList ** headNode)
{

}
*/

int main()
{
  FILE * fPtr = fopen("graph.txt"); // open file for reading
  readFile(fPtr); // read file
  fclose(fPtr); // close file

  freeNodes(struct adjList ** headNode); // free all allocated nodes/full list
}
