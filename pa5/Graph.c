//Ricky Zhao
//Rjzhao
//pa5

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Graph.h"

#define WHITE 33333333
#define GREY 44444444
#define BLACK 55555555
/***Struct************************/
typedef struct GraphObj{
	int size;
	int order;
	int source;
	int *color;
	int *parent;
	int *discover;
	int *finish;
	List *adjacency;
}GraphObj;

typedef GraphObj* Graph;
void visit(Graph G, List S, int u, int *t);

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->parent = malloc((n+1)*sizeof(int));
	G->color = malloc((n+1)*sizeof(int));
	G->adjacency = malloc((n+1)*sizeof(List));
	G->discover = malloc((n+1)*sizeof(int));
	G->finish = malloc((n+1)*sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i =1; i<=n;i++){
		G->adjacency[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return G;
}

void freeGraph(Graph* pG){
	Graph G = *pG;
	for(int i = 1;i<=getOrder(G);i++){
		freeList(&(G->adjacency[i]));
	}
	free(G->color);
	free(G->parent);
	free(G->discover);
	free(G->finish);
	free(G->adjacency);
	G->color = NULL;
	G->parent = NULL;
	G->adjacency = NULL;
	G->discover = NULL;
	G->finish = NULL;
	G = NULL;
	free(*pG);
	*pG = NULL;
}
/*** Access functions ***/
//Gets the number of vertices of a graph
int getOrder(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getOrder called on a NULL Graph\n");
		exit(1);
	}
	return G-> order;
}
//Gets the number of vertices of a graph
int getSize(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getSize called on a NULL Graph\n");
		exit(1);
	}
	return G-> size;
}

//Gets the parent of a vertex, returns NIL if there are no parent
int getParent(Graph G, int u){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getParent called on a NULL Graph\n");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getParent called on an invalid vertex\n");
		exit(1);
	}
	return G->parent[u];
}

//Gets the discover time of a vertex form the source, returns UNDEF it was not 
//Visited
int getDiscover(Graph G, int u){
		if(G==NULL){
		fprintf(stderr, "Graph Error: getDiscovery called on a NULL Graph\n");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getDiscovery called on an invalid vertex\n");
		exit(1);
	}
	return G->discover[u];
}

//Gets the finish time of a vertex form the source, returns UNDEF it was not 
//Visited
int getFinish(Graph G, int u){
		if(G==NULL){
		fprintf(stderr, "Graph Error: getFinish called on a NULL Graph\n");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getFinish called on an invalid vertex\n");
		exit(1);
	}
	return G->finish[u];
}

/*** Manipulation procedures ***/
//deletes all edges of G, restoring it to its original
//(no edge) state
void makeNull(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: makeNull called on a NULL Graph\n");
		exit(1);
	}
	for(int i = 1;i<=getOrder(G);i++){
		clear(G->adjacency[i]);
	}
	G->size=0;
}
//insert an edge between u and v. Add u to v adjacency list
//and v to u adjacency list;
void addEdge(Graph G, int u, int v){
	if(G==NULL){
		fprintf(stderr, "Graph Error: addEdge called on a NULL Graph\n");
		exit(1);
	}
	if(u<1 ||v<1|| u>getOrder(G)||v>getOrder(G)){
		fprintf(stderr,"Graph Error: addEdge called on an invalid vertex\n");
		exit(1);
	}
	
	if(length(G->adjacency[u])<=0||front(G->adjacency[u])>v){
		prepend(G->adjacency[u],v);
		G->size++;
	}else if(back(G->adjacency[u])<v){
		append(G->adjacency[u],v);
		G->size++;
	}else{
		moveFront(G->adjacency[u]);
		while(index(G->adjacency[u])!=-1&& get(G->adjacency[u])<v){
			moveNext(G->adjacency[u]);
		}
		if(get(G->adjacency[u])>v){
			insertBefore(G->adjacency[u],v);
			G->size++;
		}
	}
	
	if(length(G->adjacency[v])<=0||front(G->adjacency[v])>u){
		prepend(G->adjacency[v],u);
	}else if(back(G->adjacency[v])<u){
		append(G->adjacency[v],u);
	}else{
		moveFront(G->adjacency[v]);
		while(index(G->adjacency[v])!=-1&& get(G->adjacency[v])<u){
			moveNext(G->adjacency[v]);
		}
		if(get(G->adjacency[v])>u){
			insertBefore(G->adjacency[v],u);
		}
	}
}

//add a direced edge from u to v, add v to u adjacency list but
//not u to v adjacency list
void addArc(Graph G, int u, int v){
	if(G==NULL){
		fprintf(stderr, "Graph Error: addArc called on a NULL Graph\n");
		exit(1);
	}
	if(u<1 ||v<1|| u>getOrder(G)||v>getOrder(G)){
		fprintf(stderr,"Graph Error: addArc called on an invalid vertex\n");
		exit(1);
	}
	
	if(length(G->adjacency[u])<=0||front(G->adjacency[u])>v){
		prepend(G->adjacency[u],v);
		G->size++;
	}else if(back(G->adjacency[u])<v){
		append(G->adjacency[u],v);
		G->size++;
	}else{
		moveFront(G->adjacency[u]);
		while(index(G->adjacency[u])!=-1 && get(G->adjacency[u])<v){
			moveNext(G->adjacency[u]);
		}
		if(get(G->adjacency[u])>v){
			insertBefore(G->adjacency[u],v);
			G->size++;
		}
	}
}
//perform the Depth-first search algorithm
void DFS(Graph G, List S){
	if(length(S)!=getOrder(G)){
		fprintf(stderr, 
		"Graph Error: DFS called of with Graph and List of Different length\n");
		exit(1);
	}
	
	for(int i=1;i<=getOrder(G);i++){
		G->color[i] = WHITE;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->parent[i] = NIL;
	}
	int time = 0;
	List vert = copyList(S);
	clear(S);
	moveFront(vert);
	while(index(vert)>=0){
		int i = get(vert);
		if(G->color[i]==WHITE){
			visit(G,S,i,&time);
		}
		moveNext(vert);
	}
	
	freeList(&vert);
	
	
}
//Go through all the adjacency of a vertex
void visit(Graph G, List S, int u, int *t){
	G->color[u] = GREY;
	*t = (*t+1);
	G->discover[u]=*t;
	moveFront(G->adjacency[u]);
	while(index(G->adjacency[u])!=-1){
		int curr = get(G->adjacency[u]);
		if(G->color[curr]==WHITE){
			G->parent[curr]=u;
			visit(G,S,curr,t);
		}
		moveNext(G->adjacency[u]);
	}
	G->color[u] = BLACK;
	*t = (*t+1);
	G->finish[u]=*t;
	prepend(S,u);
}

/*** Other operations ***/
// Overrides Object's toString method. Returns a String
// representation of this Graph consisting multiple List 
// of adjacency vertex
void printGraph(FILE* out, Graph G){
	if( out == NULL ){
		fprintf(stderr,"Graph Error: cannot print to NULL file pointer\n");
		exit(1);
	}
	if( G == NULL ){
        	fprintf(stderr,"Graph Error: cannot print NULL Graph pointer\n");
		exit(1);
	}
	
	for(int i =1;i<=getOrder(G);i++){
		List L = G->adjacency[i];
		fprintf(out,"%d: ",i);
		printList(out,L);
	}
	fprintf(out,"\n");
}
//Create a transposed Graph
Graph transpose(Graph G){
	if(G==NULL){
		fprintf(stderr,"Graph Error: transpose called on a NULL Graph\n");
	}
	Graph T = newGraph(getOrder(G));
	for(int i = 1; i<=getOrder(G);i++){
		if(length(G->adjacency[i])>0){
			moveFront(G->adjacency[i]);
			while(index(G->adjacency[i])>=0){
				int u = get(G->adjacency[i]);
				addArc(T,u,i);
				moveNext(G->adjacency[i]);
			}
		}
	}
	return T;
}
//Copy a graph
Graph copyGraph(Graph G){
	if(G==NULL){
		fprintf(stderr,"Graph Error: copyGraph called on NULL Graph\n");
	}
	Graph copy = newGraph(getOrder(G));
	for(int i = 1;i<=getOrder(G);i++){
		if(length(G->adjacency[i])>0){
			moveFront(G->adjacency[i]);
			while(index(G->adjacency[i])>=0){
				int temp = get(G->adjacency[i]);
				append(copy->adjacency[i],temp);
				moveNext(G->adjacency[i]);
			}
		}
		copy->color[i] = G->color[i];
		copy->discover[i] = G->discover[i];
		copy->finish[i] = G->finish[i];
		copy->parent[i] = G->parent[i];
	}
	return copy;
}