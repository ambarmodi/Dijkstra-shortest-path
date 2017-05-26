#include<stdio.h>
#define SIZE 5
#define INFINITY 100000
#define NOT_DEFINED -99

/*Function Declaration*/
int readFile(char*);
int dijikstra();

/* Global Graph matrix*/
int graph[SIZE][SIZE];

/*
* @brief: Starting point of the program
*/
int main(int argc,char ** argv) {
	char * input;
	if(argc!=2) {
		printf("\nError: Invalid number of arguments!");
		return 0;
	}
	input = argv[1];
	readFile(input);
	dijikstra();
	printf("\n\n");
	return 0;
}

/*
* @brief: Checks if Heap is Empty 
* @return 0-Heap is empty else 1-Heap not empty
*/
int isHeapEmpty(int heap[SIZE]) {
	int i,res=0;
	for(i=0;i<SIZE;i++) {
		if(heap[i]==1) {
			res = 1;
			break;
		}
	}
	return res;
}

/*
* @brief: Extract minimum element from the heap.
* @return: index f the minimum element
*/
int extractMin(int heap[SIZE],int dist[SIZE],int current) {
	int i,min=INFINITY,res=-1;
	for(i=0;i<SIZE;i++) {
		if(min > dist[i] && heap[i] != 0) {
			min = dist[i];
			res = i;
		}
	}
	return res;
}
/*
* @brief: Dijikstras algorithm Implementation
*/
int dijikstra() {
	int i,j,start,near,current;
	int dist[SIZE],heap[SIZE],parent[SIZE];
	/*Initialization. Start vertex is vertex 0*/
	start=current=0;
	for(i=0;i<SIZE;i++) {
		dist[i]=INFINITY; 
		heap[i]=1; //Denotes it is present in heap
		parent[i]=NOT_DEFINED;
	}
	dist[0]=0;
	
	while(isHeapEmpty(heap) == 1) {
		near = extractMin(heap,dist,current);
		if(near<0)
			break;
		heap[near]=0;
		for(i=0;i<SIZE;i++){
			if(heap[i]==1 && (dist[i] > dist[near] + graph[near][i])) {
				dist[i] = dist[near] + graph[near][i];
				parent[i] = near;
			}
		}
		current=near;
	}
	/*Prints the Output*/
	for(i=0;i<SIZE;i++) {
			if(i==start) 
				continue;
			current=i;
			if(dist[i] >=INFINITY) {
				printf("\n\n (S%d,S%d): No Path Found!",start,i);
				continue;
			}
			printf("\n\n (S%d,S%d): Distance=%d\tPath= %d",start,i,dist[i],current);
			while(1) { 
				current=parent[current];
				printf(" <-%d",current);
				if(current==start)
					break;
			}
	}
	return 0;
}

/*
* @brief: Reads the input matrix. Input must be a 5x5 matrix.
*/
int readFile(char * filename) {
	FILE *fp;
	char num[255];
	int i=0,j=0,k=0,val;

	fp = fopen(filename,"r");
	if(fp == NULL) {
		printf("\nERROR in opening the file!\n\n");
		return 0;
	}
	char ch;
	ch=fgetc(fp);
	for(i=0;i<SIZE;i++) {
		for(j=0;j<SIZE;j++) {
			k=0;
			while(ch!='\n' && ch!=',' && ch!=EOF) {
				num[k++]=ch;
				ch=fgetc(fp);
			}
			num[k]='\n';
			val = atoi(num);
			if(val == NOT_DEFINED) {
					graph[i][j]=INFINITY;
			}
			else
				graph[i][j]=val;
			
			ch=fgetc(fp);
		}
	}		
	fclose(fp);
	return 0;
}
