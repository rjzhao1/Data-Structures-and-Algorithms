//Ricky Zhao
//Rjzhao
//pa5

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"
//struct----------------------------------------------------------------------

// NodeObj
typedef struct NodeObj{
	int value;
	struct NodeObj* next;
	struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

//ListObj
typedef struct ListObj{
	Node head;
	Node tail;
	Node cursor;
	int index;
	int size;
}ListObj;
//Constructor-Deconstructor----------------------------------------------------

// newNode()
// constructor of the Node type
Node newNode(int val){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->value = val;
	N->next=N->prev=NULL;
	return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
	if(pN!=NULL&&*pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

// newList()
// constructor for the List type
List newList(void){
	List L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->head=NULL;
	L->cursor=NULL;
	L->tail=NULL;
	L->index=-1;
	L->size=0;
	return L;
}

// freeList()
// destructor for the List type
void freeList(List* pL){
	if(pL!=NULL&& *pL!=NULL){
		while(length(*pL)>0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL=NULL;
	}
}

// Access functions -----------------------------------------------------------


// Returns the number of elements in this List.
int length(List L){
	 if( L==NULL ){
      fprintf(stderr, 
         "List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return (L->size);
}

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L){
	if( L==NULL ){
		fprintf(stderr,
			"List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->index);
}

// Returns front element. Pre: length()>0
int front(List L){
	if( L==NULL ){
		fprintf(stderr,
			"List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0){
		fprintf(stderr,
			"List Error: calling front() on a empty List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->head->value);
}

// Returns back element. Pre: length()>0
int back(List L){
	if( L==NULL ){
		fprintf(stderr,
			"List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->tail->value);
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Error:calling get() on an empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor==NULL){
		fprintf(stderr,
			"List Error: calling get() on a NULL pointer\n");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->value);
}

// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B){
	if(A==NULL||B==NULL){
		fprintf(stderr,
			"List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(A)==length(B)){
		Node N = A->head;
		Node M= B->head;
		while(N!=NULL){
			if(N->value!=M->value){
				return 0;
			}
			N=N->next;
			M=M->next;
		}
		return 1;
	}
	return 0;
}
// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state.
void clear(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	while(length(L)>0){
		deleteFront(L);
	}
	L->head = NULL;
	L->tail = NULL;
	L->cursor = NULL;
	L->size = 0;
	L->index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)!=0){
		L->cursor=L->head;
		L->index=0;
	}
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)!=0){
		L->cursor=L->tail;
		L->index=length(L)-1;
	}
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==0){
		L->cursor=NULL;
		L->index=-1;
	}else {
		L->cursor=L->cursor->prev;
		L->index--;
	}
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==length(L)-1){
		L->cursor=NULL;
		L->index=-1;
	}else if(index(L)>=0){
		L->cursor=L->cursor->next;
		L->index++;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		Node N = newNode(data);
		L->head = N;
		L->tail = N;
	}else{
		Node N = newNode(data);
		L->head->prev = N;
		N->next = L->head;
		L->head = N;
		if(index(L)!=-1){
			L->index++;
		}
	}
	L->size++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0){
		Node N = newNode(data);
		L->head = N;
		L->tail = N;
	}else{
		Node N = newNode(data);
		N->prev = L->tail;
		L->tail->next = N;
		L->tail = N;
	}
	L->size++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Error: calling insertBefore() on a empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)<0){
		fprintf(stderr,
			"List Error: calling insertBefore() on a undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==0){
		prepend(L,data);
	}else{
		Node N = newNode(data);
		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev=N;
		L->size++;
		L->index++;
	}

}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Error: calling insertAfter() on a empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)<0){
		fprintf(stderr,
			"List Error: calling insertAfter() on a undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==length(L)-1){
		append(L,data);
	}else{
		Node N = newNode(data);
		N->prev=L->cursor;
		N->next=L->cursor->next;
		L->cursor->next->prev=N;
		L->cursor->next=N;
		L->size++;
	}
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Error: calling deleteFront() on a empty List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==1){
		if(index(L)==0){
			L->cursor=NULL;
			L->index =-1;
		}
		Node N = L->head;
		freeNode(&N);
		L->index=-1;
		L->size=0;
	}else{
		if(index(L)==0){
			L->cursor=NULL;
			L->index =-1;
		}
		Node N = L->head;
		L->head=L->head->next;
		freeNode(&N);
		if(index(L)>0){
			L->index--;
		}
	}
	L->size--;
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Error: calling deleteBack() on a empty List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==1){
		freeNode(&(L->tail));
		L->head=NULL;
		L->tail=NULL;
		L->cursor=NULL;
		L->index=-1;
	}else{
		if(index(L)==length(L)-1){
			L->cursor=NULL;
			L->index=-1;
		}
		Node N = L->tail;
		L->tail->prev->next=NULL;
		L->tail=L->tail->prev;
		freeNode(&N);
	}
	L->size--;
	
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		fprintf(stderr,
			"List Erlaror: calling delete() on a empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)<0){
		fprintf(stderr,
			"List Error: calling delete() on a undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	Node N= L->cursor;
	if(index(L)==0){
		L->head = L->head->next;
		L->head->prev =NULL;
		L->cursor=NULL;
		freeNode(&N);
	}else if(index(L)==length(L)-1){
		L->tail = L->tail->prev;
		L->tail->next=NULL;
		L->cursor=NULL;
		freeNode(&N);
	}else{
		L->cursor->prev->next=L->cursor->next;
		L->cursor->next->prev=L->cursor->prev;
		L->cursor =NULL;
		freeNode(&N);
	}
	L->index=-1;
	L->size--;
}
// // Other operations -----------------------------------------------------------

// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	if(L==NULL){
		fprintf(stderr,
			"List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N=L->head;
	while(N!=NULL){
         fprintf(out, " %d",N->value);
		 N=N->next;
	}
	fprintf(out, "\n");
}
  
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
	List List2 = newList();
	Node N = L->head;
	while(N!=NULL){
		append(List2,N->value);
		N=N->next;
	}
	return List2;
}
