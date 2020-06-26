#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]){
	FILE *in;
	FILE *in2;
	FILE *out;
	int len=0;
	char word[MAX_LEN];
	//checking for the right input
	if(argc!=3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	//opening the files needed
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
	//counts the numbers of lines
	while(fgets(word,MAX_LEN,in)!=NULL){
	  len++;
	}
	
	in2 =fopen(argv[1],"r");
    if( in2==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   
	//array for storing the words
	char ** wordList = malloc(len*sizeof(char*));
	
	//placing the lines of words into the array
	int i =0;
	while(fgets(word,MAX_LEN,in2)!=NULL){
		word[strlen(word)-1]='\0';
		wordList[i] = malloc(strlen(word)+1*sizeof(char));
		strcpy(wordList[i],word);
		i++;
	}
	
	//creating the index List for the word
	List wordInd = newList();
	
	//Putting the index of word in alphabetical order using insertion sort
	append(wordInd,0);
	for(i =1;i<len;i++){
		moveFront(wordInd);
		while(index(wordInd)!=-1&&strcmp(wordList[i],wordList[get(wordInd)])>0){
			moveNext(wordInd);
		}
		if(index(wordInd)!=-1){
			insertBefore(wordInd,i);
		}else{
			append(wordInd,i);
		}
	}
	moveFront(wordInd);
	
	//printing the word in alphabetical order to output file
	while(index(wordInd)!=-1){
		int index = get(wordInd);
		fprintf(out,"%s\n",wordList[index]);
		moveNext(wordInd);
	}
	
	//Freeing allocated memories
	for(i = 0;i<len;i++){
		free(wordList[i]);
		wordList[i]=NULL;
	}
	free(wordList);
	wordList=NULL;
	freeList(&wordInd);
	
	//closing files
	fclose(in);
	fclose(in2);
	fclose(out);
}