/*Created by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include <stdio.h>
#include <stdlib.h>

/*
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

*/

//Prototypes
List initList();//this will just set to null in the function to initialize an empty list
Node createNode(int);//create a node in our linked list
int enQueue(List*,int);//use a queue for the list
Node *deQueue(List*);
void printList(List*);//prints it out in the correct order
void freeList(List*);//frees our memory

typedef struct node
{
	int data;
	struct node * next;
}Node;

typedef struct list
{
	struct node * graph;
}List;

//?
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

int main()
{
  FILE * fPtr = fopen("graph.txt"); // open file for reading
  readFile(fPtr); // read file
  fclose(fPtr); // close file

  freeNodes(struct adjList ** headNode); // free all allocated nodes/full list
}
