/*Created by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(FILE * fPtr)
{
	//In the case that the name of the file is not pre-determined

	//void readFile(const char *TheFile)
	//{
	//	FILE *fPtr=fopen(TheFile,"r");



	int vertexA; // first number in line
	int vertexB; // second number in line
	int numOfLines = 1; // track total number of lines
	int numVertices = 1; // track total number of vertices
	int count = 0;
	int numLines = 0;

	fPtr = fopen("graph.txt", "r"); // open file for reading

	// checking if file is valid/able to be opened
	if(fPtr == NULL){
		printf("File could not be opened or read.\n");
	}
	// scan in values from file and find smallest and largest
	while(fscanf(fPtr, "%d %d", &vertexA, &vertexB) == 2)
	{
		int myList[numOfLines][2];

		// insert values into 2d array
		//myList[n][0] = vertexA;
		//myList[n][1] = vertexB;
		myList[numOfLines][0] = vertexA;
		myList[numOfLines][1] = vertexB;

		//int max = vertexB;

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
	int myList[numVertices + 1][numVertices + 1]; //= malloc(sizeof(int) * (numVertices + 1));
	int * index = malloc(sizeof(int) * (numVertices + 1));
	if(index == NULL)
	{
		printf("Index could not be malloced.\n");
		free(index);
	}


	memset(index, 0, sizeof(int) * (numVertices + 1)); // set index, increment each time an edge is added to a vertex/index

	for (int j = 1; j <= numVertices; j++)
    	{
		for (int i = 0; i < numLines; i++)
		{
			int key = -1;

			if (myList[i][0] == j)
			{
			key = myList[i][1];
			}

			if (myList[i][1] == j)
			{
				key = myList[i][0];
			}

			if (key != -1)
			{
				myList[key][index[key]] = j;
				index[key] += 1;
			}
		}
	}
	fclose(fPtr); // close file

	//print list
	for(int i=1; i<numVertices; i++){
		if(index[i]>0){
			for(int j=0; j<index[i]; j++){
				printf("%d ", myList[i][j]);
			}
			printf("\n");
		}
	}
}

int main(){
	FILE *fPtr=NULL;
	readFile(fPtr);
	return 0;
}

/*
int main(){
	//open file
	FILE *fPtr = fopen("graph.txt", "r");

	//declare variables
	int vertexA, vertexB, lineCount=0;

	//traverse each line to gain a total line count
	while(fscanf(fPtr, "%d %d", &vertexA, &vertexB)==2){
		lineCount++;
	}

	//close file and set pointer to NULL
	fclose(fPtr);
	fPtr = NULL;

	//read graph edge data
	int vertexCount = 1;

	//open file
	fPtr = fopen("graph.txt", "r");

	//set up graph
	int myGraph[lineCount][2];
	int counter = 0;

	//traverse the file
	while(fscanf(fPtr, "%d %d", &vertexA, &vertexB)==2){
		//add in edge data
		myGraph[counter][0] = vertexA;
		myGraph[counter][1] = vertexB;
		int max = vertexB;

		//find maximum vertex
		if(vertexA > max){
			max = vertexA;
		}

		if(vertexCount < max){
			vertexCount = max;
		}

		counter++;
	}
	fclose(fPtr);
	fPtr = NULL;

	//create adjList
	int adjList[vertexCount+1][vertexCount+1];
	int *myIndexes = malloc(sizeof(int) * (vertexCount + 1));
	memset(myIndexes, 0, sizeof(int) * (vertexCount + 1));

	for(int i=1; i<=vertexCount; i++){
		for(int j=0; j<lineCount; j++){
			int flag = -1;
			if(myGraph[j][0]==i){
				flag = myGraph[j][1];
			}
			if(myGraph[j][1]==i){
				flag = myGraph[j][0];
			}
			if(flag != -1){
				adjList[flag][myIndexes[flag]] = i;
				myIndexes[flag]++;
			}
		}
	}

	//print list
	for(int i=1; i<vertexCount; i++){
		if(myIndexes[i]>0){
			for(int j=0; j<myIndexes[i]; j++){
				printf("%d ", adjList[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}
*/
