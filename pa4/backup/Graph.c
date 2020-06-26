//Ricky Zhao
//Rjzhao
//pa4

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
	int *distance;
	List *adjacency;
}GraphObj;

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->parent = malloc((n+1)*sizeof(int));
	G->color = malloc((n+1)*sizeof(int));
	G->adjacency = malloc((n+1)*sizeof(List));
	G->distance = malloc((n+1)*sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i =1; i<=n;i++){
		G->adjacency[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
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
	free(G->distance);
	free(G->adjacency);
	G->color = NULL;
	G->parent = NULL;
	G->adjacency = NULL;
	G->distance = NULL;
	G = NULL;
	free(*pG);
	*pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getOrder called on a NULL Graph");
		exit(1);
	}
	return G-> order;
}
int getSize(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getSize called on a NULL Graph");
		exit(1);
	}
	return G-> size;
}
int getSource(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getSource called on a NULL Graph");
		exit(1);
	}
	return G-> source;
}
int getParent(Graph G, int u){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getParent called on a NULL Graph");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getParent called on an invalid vertex");
		exit(1);
	}
	return G->parent[u];
}
int getDist(Graph G, int u){
		if(G==NULL){
		fprintf(stderr, "Graph Error: getDist called on a NULL Graph");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getDist called on an invalid vertex");
		exit(1);
	}
	return G->distance[u];
}
void getPath(List L, Graph G, int u){
	if(G==NULL){
		fprintf(stderr, "Graph Error: getPath called on a NULL Graph");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr,"Graph Error: getPath called on an invalid vertex");
		exit(1);
	}
	
	if(G->source==NIL){
		fprintf(stderr,"Graph Error: getPath called before BFS");
	}else if(u==G->source){
		append(L,u);
	}else if(G->parent[u]==NIL){
		append(L, NIL);
	}else{
		getPath(L,G,getParent(G,u));
		append(L,u);
	}
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G==NULL){
		fprintf(stderr, "Graph Error: makeNull called on a NULL Graph");
		exit(1);
	}
	for(int i = 1;i<=getOrder(G);i++){
		clear(G->adjacency[i]);
	}
	G->size=0;
}
void addEdge(Graph G, int u, int v){
	if(G==NULL){
		fprintf(stderr, "Graph Error: addEdge called on a NULL Graph");
		exit(1);
	}
	if(u<1 ||v<1|| u>getOrder(G)||v>getOrder(G)){
		fprintf(stderr,"Graph Error: addEdge called on an invalid vertex");
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
void addArc(Graph G, int u, int v){
	if(G==NULL){
		fprintf(stderr, "Graph Error: addArc called on a NULL Graph");
		exit(1);
	}
	if(u<1 ||v<1|| u>getOrder(G)||v>getOrder(G)){
		fprintf(stderr,"Graph Error: addArc called on an invalid vertex");
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
void BFS(Graph G, int s){
	for(int i=1;i<=getOrder(G);i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->distance[s]=0;
	G->color[s]=GREY;
	G->parent[s] = NIL;
	List Queue = newList();
	append(Queue,s);
	while(length(Queue)>0){
		moveFront(Queue);
		int current = get(Queue);
		moveFront(G->adjacency[current]);
		while(index(G->adjacency[current])>=0){
			int adj = get(G->adjacency[current]);
			if(G->color[adj]==WHITE){
				append(Queue,adj);
				G->color[adj]= GREY;
				G->parent[adj]= current;
				G->distance[adj]= G->distance[current]+1;
			}
			moveNext(G->adjacency[current]);
		}
		G->color[current]=BLACK;
		deleteFront(Queue);
	}
	freeList(&Queue);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if( out == NULL ){
		fprintf(stderr,"Graph Error: cannot print to NULL file pointer");
		exit(1);
	}
	if( G == NULL ){
        	fprintf(stderr,"Graph Error: cannot print NULL Graph pointer");
		exit(1);
	}
	
	for(int i =1;i<=getOrder(G);i++){
		List L = G->adjacency[i];
		fprintf(out,"%d: ",i);
		printList(out,L);
	}
	fprintf(out,"\n");
}
