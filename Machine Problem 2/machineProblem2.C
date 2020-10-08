#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


//Represents an adjacency list node
typedef struct AdjListNode{
  int indegree; //the idea of this is to keep track of indegree
  int outdegree; //the idea of this is to keep track of outdegree
  /*for the indegree and outdegree if we keep track of this then
  we may just set it to 0 and create a separate function to tell
  where it is going*/
  int destination;
  AdjListNode *next;
}adjListNode;

//Represents and adjacency list
typedef struct AdjList{
  AdjListNode *head;
}adjList;

//Represents a graph
typedef struct Graph{
  int vertices;
  int *visited;
  AdjList *myList;
}Graph;

//Graph prototypes
AdjListNode createNode(int);
Graph createGraph(int);

//Stack Function Prototypes
AdjListNode *push(AdjList *, int);
AdjListNode *pop(AdjList *);

//Some sort of readFile function prototype will need to be added

int main(void){

}

//create a new adj list node
AdjListNode createNode(int dest){
  //Declare and allocate memory to the new node
  AdjListNode *newNode=malloc(sizeof(AdjListNode));

  //initialize our data
  newNode->indegree=0;
  newNode->outdegree=0;
  newNode->destination=dest;
  newNode->next=NULL;

  return newNode;
}

//create a graph with v amount of vertices
Graph createGraph(int v){
  //declare and allocate memory to the new graph
  Graph *newGraph=malloc(sizeof(Graph));

  newGraph->vertices=v;
  newGraph->myList=malloc(sizeof(AdjList));
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
