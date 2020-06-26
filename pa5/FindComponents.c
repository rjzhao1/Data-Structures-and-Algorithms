//Ricky Zhao
//Rjzhao
//pa5

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
	bool end = false;
	char line[MAX_LEN];
	char* token;
	int size,count=0;
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
	
	while(!end && fgets(line,MAX_LEN,in)!=NULL){
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
				end = true;
			}else{
				addArc(G,u,v);
			}
		}
	}
	
	fprintf(out,"Adjacency list representation of G: \n");
	printGraph(out,G);
	
	List S = newList();
	for(int i = 1;i<=getOrder(G); i++){
		append(S,i);
	}
	DFS(G,S);
	Graph T = transpose(G);
	DFS(T,S);
	
	int component = 0;
	moveFront(S);
	while(index(S)>=0){
		int x = get(S);
		if(x>=0){
			int p = getParent(T,x);
			if(p==NIL){
				component++;
				insertBefore(S,-1);
			}
		}
		moveNext(S);
	}
	fprintf(out, "G contains %d strongly connected components:\n", component);
	moveBack(S);
	
	List tempComp = newList();
	
	for(int i = 1;i<=component;i++){
		fprintf(out,"Component %d:",i);
		while(index(S)>=0&&get(S)!=-1){
			int temp = get(S);
			prepend(tempComp,temp);
			movePrev(S);
		}
		printList(out,tempComp);
		clear(tempComp);
		movePrev(S);
	}
	
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);
	
	fclose(in);
	fclose(out);
	
	
	return(0);
}