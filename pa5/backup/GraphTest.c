//Ricky Zhao
//Rjzhao
//pa5

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include<string.h>

int main(int argc, char* argv[]){
  Graph A = newGraph(50);
  
  printf("%d\n", getOrder(A));
  addEdge(A, 32, 10);
  addEdge(A, 5, 6);
  addEdge(A, 7, 3);
  addEdge(A, 1, 47);
  printf("%d\n",getSize(A));
  printGraph(stdout,A);
  
  makeNull(A);
 
  for(int i =1;i<getOrder(A);i++){
	addArc(A,i,i+1);
  }
  printGraph(stdout,A);
  List S = newList();
  for(int i = 1;i<=getOrder(A);i++){
	append(S,i);
  }
  DFS(A,S);
  printGraph(stdout,A);
  transpose(A);
  printGraph(stdout,A);
  printList(stdout,S);
  for(int i = 1;i<=getOrder(A);i++){
	fprintf(stdout," discover: %d finish: %d \n",
			getDiscover(A,i),getFinish(A,i));
  }
  freeList(&S);
  freeGraph(&A);
  return(0);
  
}