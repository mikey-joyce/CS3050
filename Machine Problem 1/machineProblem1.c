#include <stdio.h>

typedef struct node{
	int data;
	struct node *next;
}Node;

struct adjList{
	struct node *graph;
};

struct adjList* initList(int size)
{
  struct adjList *headNode;
  headNode = (struct adjList*)malloc(size*sizeof(struct adjList));
  if(headNode==NULL)
  {
    printf("Error at initList function");
  }
  return headNode;
}

readFile()
{
	return fPtr;
}

struct adjList* createNode(struct adjList* headNode, int a, int b)
{
	return newNode;
}

addNode()
{
     createNode	
}

bool compare(Node * prevNode, Node * curNode)
{
	// compare node for inc size	
}

printList(Node * headNode)
{
	return void;
}

int main()
{
  fopen();
  
  fclose();
}
