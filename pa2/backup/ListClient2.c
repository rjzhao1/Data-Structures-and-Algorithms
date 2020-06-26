
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
prepend(A, 1);
        prepend(A, 5);
        prepend(A, 7);
        moveFront(A);
		printf("%d\n",index(A));
        prepend(A, 45);
        prepend(A, 51);
        prepend(A, 3214);
        prepend(A, 314);
        prepend(A, 324);
        if (index(A) != 5) return 1;
        moveBack(A);
        movePrev(A);
        prepend(A, 234);
        movePrev(A);
        if (index(A) != 6) return 2;
        moveFront(A);
        movePrev(A);
        if (index(A) != -1) return 3;
        return 0;
}