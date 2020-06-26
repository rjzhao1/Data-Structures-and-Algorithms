//Ricky Zhao
//Rjzhao
//pa2

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
  BFS(A,1);
  List L = newList();
  getPath(L,A,10);
  printList(stdout,L);
  printf("%d\n",getDist(A,20));
  printf("%d\n",getParent(A,34));
  printf("%d\n",getSource(A));
  
  freeList(&L);
  freeGraph(&A);
  return(0);
  
}