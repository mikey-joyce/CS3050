#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//Represents an adjacency list node
typedef struct AdjListNode{
  int destination;
  AdjListNode *next;
}AdjListNode;

//Represents and adjacency list
typedef struct AdjList{
  AdjListNode *head;
}AdjList;

/*Basic Linked list
Used as a list that each node contains a separate adj list*/
typedef struct List{
  int indegree; //the idea of this is to keep track of indegree
  int outdegree; //the idea of this is to keep track of outdegree
  /*for the indegree and outdegree if we keep track of this then
  we may just set it to 0 and create a separate function to tell
  where it is going*/
	AdjList *myAdjList;
	List *next;
}List;

//Represents a graph
typedef struct Graph{
  int vertices;
  int *visited;
  List *myList;
}Graph;

//Graph prototypes
AdjListNode createNode(int);
Graph createGraph(int);
void addEdge(Graph *,Graph *, int, int);
void printGraph(Graph *);
void fillStack(Graph *, int, bool, int *);
void DFS(Graph *, int, bool);
void transposeGraph(Graph *, int, int);

//Stack Function Prototypes
AdjListNode *push(AdjList *, int);
AdjListNode *pop(AdjList *);

//Some sort of readFile function prototype will need to be added
void readFile(FILE * fPtr)
{
	while(fscanf(fPtr, "%d %d", &vertexA, &vertexB)==2){
		numOfLines++;
	}

}

int main(void)
{
	FILE * fPtr - fopen("graph.txt", "r");
	readFile(fPtr);

	fclose(fPtr);
	fPtr = NULL;
}

//create a new adj list node
AdjListNode createNode(int dest){
  //Declare and allocate memory to the new node
  AdjListNode *newNode=malloc(sizeof(AdjListNode));

  //check to see if malloc worked
  if(newNode){
    //initialize our data
    newNode->destination=dest;
    newNode->next=NULL;
  }

  return newNode;
}

//create a graph with v amount of vertices
Graph createGraph(int v){
  //declare and allocate memory to the new graph
  Graph *newGraph=malloc(sizeof(Graph));
  AdjList alias;

  //if malloc failed
  if(!newGraph){
    return NULL;
  }

  //set vertices to amount of vertices given and allocate memory
  newGraph->vertices=v;
  newGraph->myList=malloc(sizeof(List));

  //alias to simplify
  alias=newGraph->myList;
  alias->indegree=0;
  alias->outdegree=0;
  alias->myAdjList->head=NULL;

  //if malloc failed
  if(!alias){
    return NULL;
  }

  //traverse the list
  for(int i=0; i<=v; i++){
    List *newListNode=malloc(sizeof(List));

    //if malloc worked
    if(!newListNode){
      return NULL;
    }

    //initialize our data and increment to next
    newListNode->indegree=0;
    newListNode->outdegree=0;
    newListNode->myAdjList->head=NULL;
    alias->next=newListNode;
    alias=newListNode;
  }

  return newGraph;
}

//Stack functions
AdjListNode *push(AdjList *node, int data){
  //alias to the head
  AdjListNode myNode=node->head;

  //Create new node
	AdjListNode *newNode;
	newNode=createNode(data);

  //set new node to be the head of the list
	newNode->next=myNode;

  //return the new head
	return newNode;
}

AdjListNode *pop(AdjList *node){
  //alias to the head
  AdjListNode myNode=node->head;

  //create temp node and set it to be the next of current head node
	AdjListNode *temp;
	temp=myNode->next;

  //delete the current head node
	myNode->data=0;
	myNode->next=NULL;
	free(node);

  //return the new head
	return temp;
}
