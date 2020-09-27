#include <stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}Node;

struct adjList
{
	struct node * graph;
};

struct adjList * initList(int size)
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
  fscanf();
	return fPtr;
}

struct adjList* createNode(struct adjList** headNode, int a, int b)
{
	return newNode;
}

addNode()
{
  createNode(struct adjList ** headNode, int a, int b);	
}

int compare(Node * prevNode, Node * curNode)
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

  for(int i=0; headNode[i]->graph->next==NULL;i++)
  {
    
  }
	return;
}

freeNodes(Node ** headNode)
{

}

int main()
{
  FILE * fPtr = fopen("graph.txt");
  fPtr.readFile(fPtr);
  fclose(fPtr);

  freeNodes(Node ** headNode);
}
