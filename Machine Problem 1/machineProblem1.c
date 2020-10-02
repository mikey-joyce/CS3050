/*Created by:
Mikey Joyce
Sarah Duong
Tasha Ogoti
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

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
