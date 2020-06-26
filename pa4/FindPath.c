//Ricky Zhao
//Rjzhao
//pa4

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 1000

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	FILE *in, *out;
	bool seperate = false;
	char line[MAX_LEN];
	char* token;
	int count,size;
	Graph G;
	
	in =fopen(argv[1],"r");
    if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
	}
   
	out = fopen(argv[2],"w");
	if(out==NULL ){
		printf("Unable to write from file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	while(!seperate && fgets(line,MAX_LEN,in)!=NULL){
		count++;
		token = strtok(line," \n");
		if(count==1){
			size = atoi(token);
			G = newGraph(size);
		}else{
			int u = atoi(token);
			token = strtok(NULL," \n");
			int v = atoi(token);
			if(u==0||v==0){
				seperate = true;
			}else{
				addEdge(G,u,v);
			}
		}
	}

	printGraph(out,G);
	List path = newList();
	
	while(fgets(line,MAX_LEN,in)!=NULL){
		count++;
		token=strtok(line," \n");
		int start = atoi(token);
		token=strtok(NULL," \n");
		int end = atoi(token);
		if(start!=0&&end!=0){
			BFS(G,start);
			if(getDist(G,end)==INF){
				fprintf(out,"The distance from %d to %d is infinity\n",start,end);
				fprintf(out,"No %d-%d path exists\n",start,end);
				fprintf(out,"\n");
			}else{
				fprintf(out,"The distance from %d to %d is %d\n",
					start,end,getDist(G,end));
				clear(path);
				getPath(path,G,end);
				fprintf(out,"A shortest %d-%d path is:",start,end);
				printList(out,path);
				fprintf(out,"\n");
			}
		}
		
	}
	
	freeList(&path);
	freeGraph(&G);
	
	fclose(in);
	fclose(out);
	
	return(0);
}